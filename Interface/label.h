#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QRubberBand>
#include <QMouseEvent>
#include <QMessageBox>

class Label : public QLabel
{
    public:
        Label();

    protected:
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

    private:
        QRubberBand *rubberBand;
        QPoint origin;
};

#endif // LABEL_H
