/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/
#include <iostream>
#include <QtGui>

class LineWidget : public QWidget {
    public:
        LineWidget(QLine Line, QWidget *parent=0) : QWidget(parent) {
            _line = Line;
        }
        void paintEvent(QPaintEvent* e) {
            QPainter painter(this);
            QPen pen;      
            QBrush brush;

            // brush.setStyle(Qt::CrossPattern);
            brush.setColor(Qt::black);      

            // pen.setStyle(Qt::DashDotLine);
            pen.setWidth(3);
            pen.setBrush(Qt::black);
            pen.setCapStyle(Qt::RoundCap);
            pen.setJoinStyle(Qt::RoundJoin);

            painter.setPen(pen);
            painter.setBrush(brush);
            painter.drawLine(_line.x1(), _line.x2(), _line.y1(), _line.y2());
        };
    private:
        QLine _line;
};