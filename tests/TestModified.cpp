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
#include "TestModified.h"
#include <QSignalSpy>
#include <QTest>
#include "core/Database.h"
#include "core/Group.h"
#include "core/Metadata.h"
#include "core/Tools.h"
#include "crypto/Crypto.h"
QTEST_GUILESS_MAIN(
	TestModified
)

void TestModified::initTestCase()
{
	QVERIFY(
		Crypto::init()
	);
}

void TestModified::testSignals()
{
	int spyCount = 0;
	int spyCount2 = 0;
	CompositeKey compositeKey;
	Database* db = new Database();
	Group* root = db->getRootGroup();
	QSignalSpy spyModified(
		db,
		SIGNAL(
			modifiedImmediate()
		)
	);
	db->setKey(
		compositeKey
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	Group* g1 = new Group();
	g1->setParent(
		root
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	Group* g2 = new Group();
	g2->setParent(
		root
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	g2->setParent(
		root,
		0
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	Entry* entry1 = new Entry();
	entry1->setGroup(
		g1
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	Database* db2 = new Database();
	Group* root2 = db2->getRootGroup();
	QSignalSpy spyModified2(
		db2,
		SIGNAL(
			modifiedImmediate()
		)
	);
	g1->setParent(
		root2
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	QCOMPARE(
		spyModified2.count(),
		++spyCount2
	);
	entry1->setTitle(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	QCOMPARE(
		spyModified2.count(),
		++spyCount2
	);
	Entry* entry2 = new Entry();
	entry2->setGroup(
		g2
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	QCOMPARE(
		spyModified2.count(),
		spyCount2
	);
	entry2->setGroup(
		root2
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	QCOMPARE(
		spyModified2.count(),
		++spyCount2
	);
	entry2->setTitle(
		"test2"
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	QCOMPARE(
		spyModified2.count(),
		++spyCount2
	);
	Group* g3 = new Group();
	g3->setParent(
		root
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	Group* g4 = new Group();
	g4->setParent(
		g3
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	delete g4;
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	delete entry2;
	QCOMPARE(
		spyModified2.count(),
		++spyCount2
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	QCOMPARE(
		spyModified2.count(),
		spyCount2
	);
	delete db;
	delete db2;
}

void TestModified::testGroupSets()
{
	int spyCount = 0;
	Database* db = new Database();
	Group* root = db->getRootGroup();
	Group* g = new Group();
	g->setParent(
		root
	);
	QSignalSpy spyModified(
		db,
		SIGNAL(
			modifiedImmediate()
		)
	);
	root->setUuid(
		UUID::random()
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	root->setUuid(
		root->getUUID()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	root->setName(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	root->setName(
		root->getName()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	root->setNotes(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	root->setNotes(
		root->getNotes()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	root->setIcon(
		1
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	root->setIcon(
		root->getIconNumber()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	root->setIcon(
		UUID::random()
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	root->setIcon(
		root->getIconUUID()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	g->setUuid(
		UUID::random()
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	g->setUuid(
		g->getUUID()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	g->setName(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	g->setName(
		g->getName()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	g->setNotes(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	g->setNotes(
		g->getNotes()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	g->setIcon(
		1
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	g->setIcon(
		g->getIconNumber()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	g->setIcon(
		UUID::random()
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	g->setIcon(
		g->getIconUUID()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	delete db;
}

void TestModified::testEntrySets()
{
	int spyCount = 0;
	Database* db = new Database();
	Group* root = db->getRootGroup();
	Group* g = new Group();
	g->setParent(
		root
	);
	Entry* entry = new Entry();
	entry->setGroup(
		g
	);
	QSignalSpy spyModified(
		db,
		SIGNAL(
			modifiedImmediate()
		)
	);
	entry->setUUID(
		UUID::random()
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setUUID(
		entry->getUUID()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setTitle(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setTitle(
		entry->getTitle()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setURL(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setURL(
		entry->getURL()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setUsername(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setUsername(
		entry->getUsername()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setPassword(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setPassword(
		entry->getPassword()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setNotes(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setNotes(
		entry->getNotes()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setIcon(
		1
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setIcon(
		entry->getIconNumber()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setIcon(
		UUID::random()
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setIcon(
		entry->getIconUUID()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setTags(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setTags(
		entry->getTags()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setExpires(
		true
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setExpires(
		entry->getTimeInfo().getExpires()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setExpiryTime(
		QDateTime::currentDateTimeUtc().addYears(
			1
		)
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setExpiryTime(
		entry->getTimeInfo().getExpiryTime()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setForegroundColor(
		Qt::red
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setForegroundColor(
		entry->getForegroundColor()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setBackgroundColor(
		Qt::red
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setBackgroundColor(
		entry->getBackgroundColor()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->setOverrideURL(
		"test"
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->setOverrideURL(
		entry->getOverrideURL()
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->getAttributes()->set(
		"test key",
		"test value",
		false
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->getAttributes()->set(
		"test key",
		entry->getAttributes()->getValue(
			"test key"
		),
		false
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	entry->getAttributes()->set(
		"test key",
		entry->getAttributes()->getValue(
			"test key"
		),
		true
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->getAttributes()->set(
		"test key",
		"new test value",
		true
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->getAttributes()->set(
		"test key2",
		"test value2",
		true
	);
	QCOMPARE(
		spyModified.count(),
		++spyCount
	);
	entry->getAttributes()->set(
		"test key2",
		entry->getAttributes()->getValue(
			"test key2"
		),
		true
	);
	QCOMPARE(
		spyModified.count(),
		spyCount
	);
	delete db;
}

void TestModified::testHistoryItem()
{
	Entry* entry = new Entry();
	QDateTime created = entry->getTimeInfo().getCreationTime();
	entry->setUUID(
		UUID::random()
	);
	entry->setTitle(
		"a"
	);
	entry->setTags(
		"a"
	);
	EntryAttributes* attributes = new EntryAttributes();
	attributes->copyCustomKeysFrom(
		entry->getAttributes()
	);
	Entry* historyEntry;
	int historyItemsSize = 0;
	entry->beginUpdate();
	entry->setTitle(
		"a"
	);
	entry->setTags(
		"a"
	);
	entry->setOverrideURL(
		""
	);
	entry->endUpdate();
	QCOMPARE(
		entry->getHistoryItems().size(),
		historyItemsSize
	);
	QDateTime modified = entry->getTimeInfo().getLastModificationTime();
	QTest::qSleep(
		10
	);
	entry->beginUpdate();
	entry->setTitle(
		"b"
	);
	entry->endUpdate();
	QCOMPARE(
		entry->getHistoryItems().size(),
		++historyItemsSize
	);
	historyEntry = entry->getHistoryItems().at(
		historyItemsSize - 1
	);
	QCOMPARE(
		historyEntry->getTitle(),
		QString("a")
	);
	QCOMPARE(
		historyEntry->getUUID(),
		entry->getUUID()
	);
	QCOMPARE(
		historyEntry->getTags(),
		entry->getTags()
	);
	QCOMPARE(
		historyEntry->getOverrideURL(),
		entry->getOverrideURL()
	);
	QCOMPARE(
		historyEntry->getTimeInfo().getCreationTime(),
		created
	);
	QCOMPARE(
		historyEntry->getTimeInfo().getLastModificationTime(),
		modified
	);
	QCOMPARE(
		historyEntry->getHistoryItems().size(),
		0
	);
	entry->beginUpdate();
	entry->setTags(
		"b"
	);
	entry->endUpdate();
	QCOMPARE(
		entry->getHistoryItems().size(),
		++historyItemsSize
	);
	QCOMPARE(
		entry->getHistoryItems().at(historyItemsSize - 1)->getTags(),
		QString("a")
	);
	entry->beginUpdate();
	entry->getAttachments()->set(
		"test",
		QByteArray(
			"value"
		)
	);
	entry->endUpdate();
	QCOMPARE(
		entry->getHistoryItems().size(),
		++historyItemsSize
	);
	QCOMPARE(
		entry->getHistoryItems().at(historyItemsSize - 1)->getAttachments()->
		getKeys(). size(),
		0
	);
	attributes->set(
		"k",
		"myvalue"
	);
	entry->beginUpdate();
	entry->getAttributes()->copyCustomKeysFrom(
		attributes
	);
	entry->endUpdate();
	QCOMPARE(
		entry->getHistoryItems().size(),
		++historyItemsSize
	);
	QVERIFY(
		!entry->getHistoryItems().at(historyItemsSize - 1)->getAttributes()->
		getKeys(). contains("k")
	);
	delete attributes;
	delete entry;
	Database* db = new Database();
	Group* root = db->getRootGroup();
	db->getMetadata()->setHistoryMaxItems(
		3
	);
	db->getMetadata()->setHistoryMaxSize(
		-1
	);
	Entry* historyEntry2;
	Entry* entry2 = new Entry();
	entry2->setGroup(
		root
	);
	entry2->beginUpdate();
	entry2->setTitle(
		"1"
	);
	entry2->endUpdate();
	entry2->beginUpdate();
	entry2->setTitle(
		"2"
	);
	entry2->endUpdate();
	entry2->beginUpdate();
	entry2->setTitle(
		"3"
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		3
	);
	entry2->beginUpdate();
	entry2->setTitle(
		"4"
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		3
	);
	db->getMetadata()->setHistoryMaxItems(
		1
	);
	entry2->beginUpdate();
	entry2->setTitle(
		"5"
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		1
	);
	historyEntry2 = entry2->getHistoryItems().at(
		0
	);
	QCOMPARE(
		historyEntry2->getTitle(),
		QString("4")
	);
	db->getMetadata()->setHistoryMaxItems(
		-1
	);
	for(int i = 0; i < 20; i++)
	{
		entry2->beginUpdate();
		entry2->setTitle(
			"6"
		);
		entry2->endUpdate();
		entry2->beginUpdate();
		entry2->setTitle(
			"6b"
		);
		entry2->endUpdate();
	}
	QCOMPARE(
		entry2->getHistoryItems().size(),
		41
	);
	db->getMetadata()->setHistoryMaxItems(
		0
	);
	entry2->beginUpdate();
	entry2->setTitle(
		"7"
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		0
	);
	db->getMetadata()->setHistoryMaxItems(
		-1
	);
	db->getMetadata()->setHistoryMaxSize(
		17000
	);
	entry2->beginUpdate();
	entry2->getAttachments()->set(
		"test",
		QByteArray(
			18000,
			'X'
		)
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		1
	);
	historyEntry2 = entry2->getHistoryItems().at(
		0
	);
	QCOMPARE(
		historyEntry2->getTitle(),
		QString("7")
	);
	entry2->beginUpdate();
	entry2->setTitle(
		"8"
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		2
	);
	entry2->beginUpdate();
	entry2->getAttachments()->remove(
		"test"
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		0
	);
	entry2->beginUpdate();
	entry2->getAttachments()->set(
		"test2",
		QByteArray(
			6000,
			'a'
		)
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		1
	);
	entry2->beginUpdate();
	entry2->getAttachments()->set(
		"test3",
		QByteArray(
			6000,
			'b'
		)
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		2
	);
	entry2->beginUpdate();
	entry2->getAttachments()->set(
		"test4",
		QByteArray(
			6000,
			'c'
		)
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		3
	);
	entry2->beginUpdate();
	entry2->getAttachments()->set(
		"test5",
		QByteArray(
			6000,
			'd'
		)
	);
	entry2->endUpdate();
	QCOMPARE(
		entry2->getHistoryItems().size(),
		4
	);
	Entry* entry3 = new Entry();
	entry3->setGroup(
		root
	);
	QCOMPARE(
		entry3->getHistoryItems().size(),
		0
	);
	entry3->beginUpdate();
	entry3->getAttachments()->set(
		"test",
		QByteArray(
			6000,
			'a'
		)
	);
	entry3->endUpdate();
	QCOMPARE(
		entry3->getHistoryItems().size(),
		1
	);
	entry3->beginUpdate();
	entry3->getAttachments()->set(
		"test",
		QByteArray(
			6000,
			'b'
		)
	);
	entry3->endUpdate();
	QCOMPARE(
		entry3->getHistoryItems().size(),
		2
	);
	entry3->beginUpdate();
	entry3->getAttachments()->set(
		"test",
		QByteArray(
			6000,
			'c'
		)
	);
	entry3->endUpdate();
	QCOMPARE(
		entry3->getHistoryItems().size(),
		3
	);
	entry3->beginUpdate();
	entry3->getAttachments()->set(
		"test",
		QByteArray(
			6000,
			'd'
		)
	);
	entry3->endUpdate();
	QCOMPARE(
		entry3->getHistoryItems().size(),
		2
	);
	delete db;
}
