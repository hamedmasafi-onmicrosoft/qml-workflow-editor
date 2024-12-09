#pragma once

#include <QQuickItem>
#include <QUndoStack>

class Block;
class AbstractTool;
class RelationHandle;
class AbstractRelation;
class WorkFlowEditorArea : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(
        Tool selectedTool READ selectedTool WRITE setSelectedTool NOTIFY selectedToolChanged FINAL)
    Q_PROPERTY(QQmlComponent *highlightComponent READ highlightComponent WRITE setHighlightComponent
                   NOTIFY highlightComponentChanged FINAL)
    Q_PROPERTY(QQmlComponent *relationComponent READ relationComponent WRITE setRelationComponent
                   NOTIFY relationComponentChanged FINAL)

public:
    enum class Tool { None, Select, Relation };
    Q_ENUM(Tool)

    WorkFlowEditorArea(QQuickItem *parent = nullptr);
    void componentComplete() override;

    Q_INVOKABLE QQuickItem *addBlock(QQmlComponent *block, const QVariantMap &props);
    Q_INVOKABLE QQuickItem *addMiddleBlock(QQmlComponent *block,
                                           AbstractRelation *relation,
                                           const QVariantMap &props);

    Q_INVOKABLE AbstractRelation *addRelation(Block *from, Block *to);
    Q_INVOKABLE AbstractRelation *addRelation(RelationHandle *from, RelationHandle *to);

    QQmlComponent *highlightComponent() const;
    void setHighlightComponent(QQmlComponent *newHighlightComponent);

    Tool selectedTool() const;
    void setSelectedTool(Tool newSelectedTool);

    QQmlComponent *relationComponent() const;
    void setRelationComponent(QQmlComponent *newRelationComponent);

protected:
    bool childMouseEventFilter(QQuickItem *, QEvent *);

Q_SIGNALS:
    void highlightComponentChanged();

    void selectedToolChanged();

    void relationComponentChanged();

private:
    QList<QQuickItem *> _blocks;

    void createTools();
    void tool_activated();

    QUndoStack _undoStack;
    AbstractTool *_activeTool{nullptr};
    QMap<Tool, AbstractTool *> _tools;
    QQmlComponent *m_highlightComponent = nullptr;
    Tool m_selectedTool{Tool::None};
    QQmlComponent *m_relationComponent = nullptr;
};
