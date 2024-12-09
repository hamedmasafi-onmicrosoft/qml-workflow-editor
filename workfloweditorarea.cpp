#include "workfloweditorarea.h"

#include "commands/addblockcommand.h"

#include "block.h"
#include "directrelation.h"
#include "relationtool.h"
#include "selecttool.h"

#include <QDebug>
#include <QMouseEvent>
#include <QQmlEngine>

WorkFlowEditorArea::WorkFlowEditorArea(QQuickItem *parent)
    : QQuickItem{parent}
{
    setFiltersChildMouseEvents(true);
    setAcceptHoverEvents(true);
    setAcceptHoverEvents(true);
}

QQuickItem *WorkFlowEditorArea::addBlock(QQmlComponent *block, const QVariantMap &props)
{
    auto cmd = new AddBlockCommand{this, block, props};
    _undoStack.push(cmd);
    return cmd->_childItem;
}

QQuickItem *WorkFlowEditorArea::addMiddleBlock(QQmlComponent *block,
                                               AbstractRelation *relation,
                                               const QVariantMap &props)
{
    auto cmd = new AddBlockCommand{this, block, props};
    _undoStack.push(cmd);
    auto newBlock = qobject_cast<Block *>(cmd->_childItem);

    newBlock->setPosition({relation->x() + (relation->width() - newBlock->width()) / 2,
                           relation->y() + (relation->height() - newBlock->height()) / 2});

    auto to = relation->endHandle();
    relation->setEndHandle(newBlock->handles(RelationHandle::HandleType::Input).first());
    addRelation(newBlock->handles(RelationHandle::HandleType::Output).first(), to);
    return newBlock;
}

AbstractRelation *WorkFlowEditorArea::addRelation(Block *from, Block *to)
{
    auto fromList = from->handles(RelationHandle::HandleType::Output);
    auto toList = to->handles(RelationHandle::HandleType::Input);

    if (!fromList.size() || !toList.size())
        return nullptr;

    return addRelation(fromList.first(), toList.first());
}

AbstractRelation *WorkFlowEditorArea::addRelation(RelationHandle *from, RelationHandle *to)
{
    AbstractRelation *rel{};
    if (m_relationComponent) {
        auto context = QQmlEngine::contextForObject(m_relationComponent); // Get a valid context
        if (!context) {
            qDebug() << "Failed to get a valid QQmlContext!";
            return nullptr;
        }

        auto obj = m_relationComponent->create(context);
        rel = qobject_cast<AbstractRelation *>(obj);
    }
    if (!rel)
        rel = new DirectRelation{this};
    rel->setArea(this);
    rel->setParentItem(this);
    rel->setStartHandle(from);
    rel->setEndHandle(to);
    rel->setZ(15);
    rel->setVisible(true);

    from->setState(RelationHandle::HandleState::Connected);
    to->setState(RelationHandle::HandleState::Connected);
    return rel;
}

bool WorkFlowEditorArea::childMouseEventFilter(QQuickItem *child, QEvent *event)
{
    if (_activeTool)
        switch (_activeTool->childMouseEventFilter(child, event)) {
        case AbstractTool::ChildMouseEventFilterResult::True:
            return true;
        case AbstractTool::ChildMouseEventFilterResult::False:
            return false;
        case AbstractTool::ChildMouseEventFilterResult::CallParent:
            return QQuickItem::childMouseEventFilter(child, event);
        }

    return QQuickItem::childMouseEventFilter(child, event);
}

void WorkFlowEditorArea::createTools()
{
    auto relTool = new RelationTool{this};

    if (m_highlightComponent) {
        auto context = QQmlEngine::contextForObject(m_highlightComponent); // Get a valid context
        if (!context) {
            qDebug() << "Failed to get a valid QQmlContext!";
            return;
        }

        auto obj = m_highlightComponent->create(context);
        auto highlightItem = qobject_cast<QQuickItem *>(obj);
        if (highlightItem) {
            highlightItem->setParentItem(this);
            highlightItem->setVisible(false);
            highlightItem->setZ(20);
            relTool->setHighlightItem(highlightItem);
        }
    }

    auto selectTool = new SelectTool{this};

    _tools.insert(Tool::Select,selectTool);
    _tools.insert(Tool::Relation, relTool);

    setSelectedTool(Tool::Select);
}

void WorkFlowEditorArea::tool_activated() {
    auto tool = qobject_cast<AbstractTool*>(sender());

    if (!tool)
        return;

    if (_activeTool)
        _activeTool->setActive(false);

    _activeTool = tool;
}

void WorkFlowEditorArea::componentComplete()
{
    createTools();
    QQuickItem::componentComplete();
}

QQmlComponent *WorkFlowEditorArea::highlightComponent() const
{
    return m_highlightComponent;
}

void WorkFlowEditorArea::setHighlightComponent(QQmlComponent *newHighlightComponent)
{
    if (m_highlightComponent == newHighlightComponent)
        return;
    m_highlightComponent = newHighlightComponent;
    emit highlightComponentChanged();
}

WorkFlowEditorArea::Tool WorkFlowEditorArea::selectedTool() const
{
    return m_selectedTool;
}

void WorkFlowEditorArea::setSelectedTool(Tool newSelectedTool)
{
    if (m_selectedTool == newSelectedTool)
        return;

    if (_activeTool)
        _activeTool->setActive(false);
    m_selectedTool = newSelectedTool;
    _activeTool = _tools.value(newSelectedTool);
    _activeTool->setActive(true);
    emit selectedToolChanged();
}

QQmlComponent *WorkFlowEditorArea::relationComponent() const
{
    return m_relationComponent;
}

void WorkFlowEditorArea::setRelationComponent(QQmlComponent *newRelationComponent)
{
    if (m_relationComponent == newRelationComponent)
        return;
    m_relationComponent = newRelationComponent;
    emit relationComponentChanged();
}
