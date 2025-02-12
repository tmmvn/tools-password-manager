/*
 *  Copyright (C) 2012 Felix Geyer <debfx@fobos.de>
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
#ifndef KEEPASSX_CLIPBOARD_H
#define KEEPASSX_CLIPBOARD_H
#include <QObject>
class QTimer;

class Clipboard final:public QObject
{
	Q_OBJECT public:
	void setText(
		const QString &text
	);
	static Clipboard* getInstance();
public Q_SLOTS:
	void do_clearCopiedText();
private Q_SLOTS:
	void do_clearClipboard();
private:
	explicit Clipboard(
		QObject* parent = nullptr
	);
	static Clipboard* instance;
	QTimer* timer;
	QString lastCopied;
};
#endif // KEEPASSX_CLIPBOARD_H
