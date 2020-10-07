#include "start_screen.h"

Start_Screen::Start_Screen(QWidget* parent):
	QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.start, SIGNAL(clicked()), this, SLOT(OnStartClicked()));
}

void Start_Screen::OnStartClicked() {
	this->deleteLater();
}

Start_Screen::~Start_Screen() {

}