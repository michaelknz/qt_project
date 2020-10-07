#include <QWidget>
#include "ui_start_screen.h"

class Start_Screen :public QWidget {
	Q_OBJECT

public:
	Start_Screen(QWidget* parent = 0);
	~Start_Screen();

public slots:
	void OnStartClicked();

private:
	Ui::Form ui;
};