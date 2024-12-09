#include "block.h"

#include <QDebug>

Block::Block(QQuickItem *parent)
    : QQuickItem(parent)
    , m_dragging(false)
{
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
}

QList<RelationHandle *> Block::handles(RelationHandle::HandleType type) {
    auto list = findChildren<RelationHandle*>();
    QList<RelationHandle *> ret;
    std::copy_if(list.begin(), list.end(), std::back_inserter(ret), [&type](RelationHandle *h){
        return h->type() == type;
    });
    return ret;
}

void Block::mousePressEvent(QMouseEvent *event)
{
//     if (event->button() == Qt::LeftButton) {
//         m_dragging = true;
//         m_lastMousePosition = event->pos();
//     }
//     QQuickItem::mousePressEvent(event);
//     event->accept();
//     qDebug() << "!" << position();

    QQuickItem::mousePressEvent(event);
    event->accept();
}

// void Block::mouseMoveEvent(QMouseEvent *event)
// {
//     if (m_dragging) {
//         QPointF delta = event->pos() - m_lastMousePosition;
//         setPosition(position() + delta);
//         qDebug() << position();
//         Q_EMIT moving();
//     }
//     QQuickItem::mouseMoveEvent(event);
// }

// void Block::mouseReleaseEvent(QMouseEvent *event)
// {
//     if (event->button() == Qt::LeftButton) {
//         m_dragging = false;
//     }
//     QQuickItem::mouseReleaseEvent(event);
// }
