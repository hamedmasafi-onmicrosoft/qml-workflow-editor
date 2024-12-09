#include "relation.h"

#include "block.h"
#include "workfloweditorarea.h"

namespace {
constexpr int margin{10};
}

Relation::Relation(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_startPoint(0, 0)
    , m_endPoint(0, 0)
{
    updateGeometry();
}

QPointF Relation::startPoint() const
{
    return m_startPoint;
}

void Relation::setStartPoint(const QPointF &point)
{
    if (m_startPoint != point) {
        m_startHandle = nullptr;
        m_startPoint = point;
        emit startPointChanged();
        updateGeometry();
        update();
    }
}

QPointF Relation::endPoint() const
{
    return m_endPoint;
}

void Relation::setEndPoint(const QPointF &point)
{
    if (m_endPoint != point) {
        m_endHandle = nullptr;
        m_endPoint = point;
        emit endPointChanged();
        updateGeometry();
        update();
    }
}

void Relation::paint(QPainter *painter)
{
    // painter->fillRect(boundingRect(), Qt::yellow);
    QPainterPath path;

    QPointF controlPoint1;
    QPointF controlPoint2;
    switch (_lineType) {
    case Relation::LineType::FlineHori:
        controlPoint1 = QPointF{width() / 2, 0};
        controlPoint2 = QPointF{width() / 2, height()};
        path.moveTo({margin, margin});
        path.cubicTo(controlPoint1, controlPoint2, {width() - margin, height() - margin});
        break;
    case Relation::LineType::BLineHori:
        controlPoint1 = QPointF{width() / 2, height()};
        controlPoint2 = QPointF{width() / 2, 0};
        path.moveTo({margin, height() - margin});
        path.cubicTo(controlPoint1, controlPoint2, {width() - margin, margin});
        break;
    }

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::black, 2));
    painter->drawPath(path);
}

void Relation::updateGeometry()
{
    QPointF startPoint;
    QPointF endPoint;
    if (m_startHandle)
        startPoint = m_startHandle->mapToItem(_area,
                                              m_startHandle->width() / 2,
                                              m_startHandle->height() / 2);
    else
        startPoint = m_startPoint;

    if (m_endHandle)
        endPoint = m_endHandle->mapToItem(_area,
                                          m_endHandle->width() / 2,
                                          m_endHandle->height() / 2);
    else
        endPoint = m_endPoint;

    if ((startPoint.x() > endPoint.x() && startPoint.y() > endPoint.y())
        || (startPoint.x() < endPoint.x() && startPoint.y() < endPoint.y()))
        _lineType = LineType::FlineHori;
    else
        _lineType = LineType::BLineHori;

    QRectF boundingRect;
    boundingRect.setTopLeft(
        QPointF(qMin(startPoint.x(), endPoint.x()), qMin(startPoint.y(), endPoint.y())));
    boundingRect.setBottomRight(
        QPointF(qMax(startPoint.x(), endPoint.x()), qMax(startPoint.y(), endPoint.y())));
    boundingRect.adjust(-margin, -margin, margin, margin); // Add some margin for the curve
    setX(boundingRect.x());
    setY(boundingRect.y());
    setWidth(boundingRect.width());
    setHeight(boundingRect.height());
}

WorkFlowEditorArea *Relation::area() const
{
    return _area;
}

void Relation::setArea(WorkFlowEditorArea *newArea)
{
    _area = newArea;
}

RelationHandle *Relation::startHandle() const
{
    return m_startHandle;
}

void Relation::setStartHandle(RelationHandle *newStartHandle)
{
    if (m_startHandle == newStartHandle)
        return;

    if (m_startHandle)
        disconnect(m_startHandle->parentBlock(), nullptr, this, nullptr);
    m_startHandle = newStartHandle;
    updateGeometry();
    emit startHandleChanged();

    connect(newStartHandle->parentBlock(), &Block::moving, this, &Relation::updateGeometry);
}

RelationHandle *Relation::endHandle() const
{
    return m_endHandle;
}

void Relation::setEndHandle(RelationHandle *newEndHandle)
{
    if (m_endHandle == newEndHandle)
        return;

    if (m_endHandle)
        disconnect(m_endHandle->parentBlock(), nullptr, this, nullptr);

    m_endHandle = newEndHandle;
    updateGeometry();
    emit endHandleChanged();

    connect(newEndHandle->parentBlock(), &Block::moving, this, &Relation::updateGeometry);
}
