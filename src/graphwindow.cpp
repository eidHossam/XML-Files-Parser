#include "graphwindow.h"
#include <graphviz/gvc.h>

GraphWindow::GraphWindow(QWidget *parent) : QDialog(parent)
{
    scene = new QGraphicsScene(this);

    // Create a view to display the scene
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::SmoothPixmapTransform);
    view->setSceneRect(0, 0, 500, 500); // Set the initial scene size

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);

    setWindowTitle("Graph Window");
    setMinimumSize(300, 300); // Set the minimum size for the window
}

void GraphWindow::addGraphNode(qreal x, qreal y)
{
    // Create a ellipse item as a graph node
    QGraphicsEllipseItem *nodeItem = new QGraphicsEllipseItem(x, y, 30, 30);
    nodeItem->setBrush(Qt::blue); // Set node color

    // Add the node to the scene
    scene->addItem(nodeItem);
}
