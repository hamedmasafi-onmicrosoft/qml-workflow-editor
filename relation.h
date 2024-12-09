#pragma once

#include "relationhandle.h"

#include <QPainter>
#include <QPainterPath>
#include <QQuickPaintedItem>

class WorkFlowEditorArea;
class Relation : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QPointF startPoint READ startPoint WRITE setStartPoint NOTIFY startPointChanged FINAL)
    Q_PROPERTY(QPointF endPoint READ endPoint WRITE setEndPoint NOTIFY endPointChanged FINAL)

    Q_PROPERTY(RelationHandle* startHandle READ startHandle WRITE setStartHandle NOTIFY startHandleChanged FINAL)
    Q_PROPERTY(RelationHandle* endHandle READ endHandle WRITE setEndHandle NOTIFY endHandleChanged FINAL)

public:
    enum class LineType {
        BLineHori, /* //  */
        FlineHori  /* \\  */
    };
    Q_ENUM(LineType)
    Relation(QQuickItem *parent = nullptr);

    QPointF startPoint() const;
    void setStartPoint(const QPointF &point);

    QPointF endPoint() const;
    void setEndPoint(const QPointF &point);

    void paint(QPainter *painter) override;

    RelationHandle *startHandle() const;
    void setStartHandle(RelationHandle *newStartHandle);

    RelationHandle *endHandle() const;
    void setEndHandle(RelationHandle *newEndHandle);

    WorkFlowEditorArea *area() const;
    void setArea(WorkFlowEditorArea *newArea);

signals:
    void startPointChanged();
    void endPointChanged();
    void startHandleChanged();
    void endHandleChanged();

private:

    LineType _lineType;
    QPointF m_startPoint;
    QPointF m_endPoint;

    void updateGeometry();
    RelationHandle *m_startHandle = nullptr;
    RelationHandle *m_endHandle = nullptr;
    WorkFlowEditorArea *_area;
};
