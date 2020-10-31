#include <QWidget>
#include "ui_start_screen.h"
#include "DataBase.h"

class Start_Screen :public QWidget {
	Q_OBJECT

public:
	Start_Screen(QWidget* parent = 0);
	~Start_Screen();
	bool GetIsContinue();
	bool GetIsQuit();

public slots:
	void OnStartClicked();
	void OnContinueClicked();
	void OnQuitClicked();

private:
	Ui::Form ui;
	bool is_continue;
	bool is_quit;
};