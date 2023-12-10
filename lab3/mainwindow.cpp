#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(700, 600);

    mainWidget = new QWidget();
    vBoxLayout = new QVBoxLayout(mainWidget);
    auto hBoxLayout = new QHBoxLayout();


    mirrorButton = new QPushButton("Reverse Text");
    connect(mirrorButton, &QPushButton::clicked, this, &MainWindow::handleMirrorButtonClick);

    textEdit = new QTextEdit("Write your own text...");

    outputTextEdit = new QTextEdit("Hello, World!");
    outputTextEdit->setReadOnly(true);

    graphButton = new QPushButton("Generate Graph");
    connect(graphButton, &QPushButton::clicked, this, &MainWindow::handleGraphButtonClick);

    graphicsView = new QGraphicsView();
    scene = new QGraphicsScene();
    graphicsView->setScene(scene);

    vBoxLayout->addLayout(hBoxLayout);
    vBoxLayout->addWidget(mirrorButton);
    hBoxLayout->addWidget(textEdit);
    hBoxLayout->addWidget(outputTextEdit);

    auto spacer = new QSpacerItem(0, 25);
    vBoxLayout->addSpacerItem(spacer);

    vBoxLayout->addWidget(graphicsView);
    vBoxLayout->addWidget(graphButton);

    this->setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleMirrorButtonClick()
{
    QString text = textEdit->toPlainText();
    std::reverse(text.begin(), text.end());
    outputTextEdit->setPlainText(text);
}

void MainWindow::handleGraphButtonClick()
{
    scene->clear();
    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    float x = -M_PI;
    float y = std::sin(x);
    float scale = 100;
    QPointF previousPoint(200 + scale * x, 100 - scale * y);

    int totalPoints = 1000;
    float step = 2 * M_PI / totalPoints;

    for (int i = 0; i < totalPoints; i++)
    {
        y = std::sin(x);
        QPointF point(200 + scale * x, 100 - scale * y);
        scene->addLine(QLineF(previousPoint, point), pen);
        previousPoint = point;

        x += step;
    }
}
