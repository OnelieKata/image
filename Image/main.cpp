#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //test pull1
    QPushButton bouton("Salut les Zéros, la forme ?");
    bouton.show();

    return app.exec();
    //return n2
}
