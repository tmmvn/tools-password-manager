/*
 *  Copyright (C) 2014 Felix Geyer <debfx@fobos.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef KEEPASSX_PASSWORDEDIT_H
#define KEEPASSX_PASSWORDEDIT_H
#include <QLineEdit>

class PasswordEdit final:public QLineEdit
{
	Q_OBJECT public:
	static const QColor CorrectSoFarColor;
	static const QColor ErrorColor;
	explicit PasswordEdit(
		QWidget* parent = nullptr
	);
	void enableVerifyMode(
		PasswordEdit* baseEdit
	);
public Q_SLOTS:
	void do_setShowPassword(
		bool show
	);
Q_SIGNALS:
	void sig_showPasswordChanged(
		bool show
	);
private Q_SLOTS:
	void do_updateStylesheet();
private:
	bool passwordsEqual() const;
	PasswordEdit* basePasswordEdit;
};
#endif // KEEPASSX_PASSWORDEDIT_H
