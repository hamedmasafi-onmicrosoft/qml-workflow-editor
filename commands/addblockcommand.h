#pragma once

#include <QUndoCommand>
#include <QVariantMap>

class QQuickItem;
class QQmlComponent;

class AddBlockCommand : public QUndoCommand
{
public:
    AddBlockCommand(QQuickItem *parent, QQmlComponent *childComponent, const QVariantMap &props = {});

    void undo() override;
    void redo() override;

private:
    QQuickItem *_parent;
    QQmlComponent *_childComponent;
    QVariantMap _props;
    QQuickItem *_childItem;

    friend class WorkFlowEditorArea;
};
