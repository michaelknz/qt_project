#include "start_screen.h"

Start_Screen::Start_Screen(QWidget* parent):
	QWidget(parent)
{
	ui.setupUi(this);
	if (!(DataBase::Have_DataBase())) {
		ui.contin->setDisabled(true);
	}
	is_quit = false;

	QObject::connect(ui.start, SIGNAL(clicked()), this, SLOT(OnStartClicked()));
	QObject::connect(ui.contin, SIGNAL(clicked()), this, SLOT(OnContinueClicked()));
	QObject::connect(ui.quit, SIGNAL(clicked()), this, SLOT(OnQuitClicked()));
}

void Start_Screen::OnStartClicked() {
	is_continue = false;
	this->deleteLater();
}

void Start_Screen::OnContinueClicked() {
	is_continue = true;
	this->deleteLater();
}

void Start_Screen::OnQuitClicked() {
	is_quit = true;
	this->deleteLater();
}

bool Start_Screen::GetIsContinue() {
	return is_continue;
}

bool Start_Screen::GetIsQuit() {
	return is_quit;
}

Start_Screen::~Start_Screen() {

}