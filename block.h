#pragma once

#include <QQuickItem>
#include <QMouseEvent>
#include "relationhandle.h"

class Block : public QQuickItem {
    Q_OBJECT
    QML_ELEMENT

public:
    Block(QQuickItem *parent = nullptr);

    QList<RelationHandle *> handles(RelationHandle::HandleType type);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    // void mouseMoveEvent(QMouseEvent *event) override;

    // void mouseReleaseEvent(QMouseEvent *event) override;

Q_SIGNALS:
    void moving();

private:
    bool m_dragging;
    QPointF m_lastMousePosition;
};
