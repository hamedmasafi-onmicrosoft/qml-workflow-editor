#include "workfloweditorarea.h"

#include "commands/addblockcommand.h"

#include "block.h"
#include "relation.h"
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

Relation *WorkFlowEditorArea::addRelation(Block *from, Block *to)
{
    auto fromList = from->handles(RelationHandle::HandleType::Output);
    auto toList = to->handles(RelationHandle::HandleType::Input);

    if (!fromList.size() || !toList.size())
        return nullptr;

    return addRelation(fromList.first(), toList.first());
}

Relation *WorkFlowEditorArea::addRelation(RelationHandle *from, RelationHandle *to)
{
    Relation *rel{};
    if (m_relationComponent) {
        auto context = QQmlEngine::contextForObject(m_relationComponent); // Get a valid context
        if (!context) {
            qDebug() << "Failed to get a valid QQmlContext!";
            return nullptr;
        }

        auto obj = m_relationComponent->create(context);
        rel = qobject_cast<Relation *>(obj);
    }
    if (!rel)
        rel = new Relation{this};
    rel->setArea(this);
    rel->setParentItem(this);
    rel->setStartHandle(from);
    rel->setEndHandle(to);
    rel->setZ(15);
    rel->setVisible(true);
    return rel;
}

bool WorkFlowEditorArea::childMouseEventFilter(QQuickItem *child, QEvent *event)
{
    // switch (event->type()) {
    // case QEvent::MouseButtonPress: {
    //     qDebug() << "press";
    //     QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    //     if (mouseEvent->button() == Qt::LeftButton) {
    //         // Handle mouse press event for the child
    //         qDebug() << "Mouse pressed on child at position:" << mouseEvent->pos();
    //         return false; // Continue with default processing
    //     }
    //     break;
    // }
    // case QEvent::MouseMove: {
    //     QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    //     // Handle mouse move event for the child
    //     qDebug() << "Mouse moved on child to position:" << mouseEvent->pos();
    //     return false; // Continue with default processing
    // }
    // case QEvent::MouseButtonRelease: {
    //     QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    //     if (mouseEvent->button() == Qt::LeftButton) {
    //         // Handle mouse release event for the child
    //         qDebug() << "Mouse released on child at position:" << mouseEvent->pos();
    //         return false; // Continue with default processing
    //     }
    //     break;
    // }
    // default:
    //     break;
    // }

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
