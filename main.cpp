#include <QtGui/QApplication>
#include "mainwindow.h"
#include "Query1.h"
#include "HypothesisObjectInMotion.h"
#include "State.h"

int main(int argc, char *argv[])
{
    State* state = State::instance();
    Query1 query;
    state->setQuery(&query);

    HypothesisObjectInMotion alt1;
    state->addAlternativeHypothesis(&alt1);

    QApplication a(argc, argv);
    MainWindow w(8, 4, 2);
    w.show();
    return a.exec();
}
