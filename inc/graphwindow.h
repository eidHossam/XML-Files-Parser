#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

class GraphWindow : public QDialog
{
    Q_OBJECT

public:
    GraphWindow(QWidget *parent = nullptr);
    void addGraphNode(qreal x, qreal y); // Function to add a graph node

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // GRAPHWINDOW_H
