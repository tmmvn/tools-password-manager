/*
*  Copyright (C) 2010 Felix Geyer <debfx@fobos.de>
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
#include "SymmetricCipher.h"
#include "config-keepassx.h"
#include "crypto/SymmetricCipherGcrypt.h"

SymmetricCipher::SymmetricCipher(
	const Algorithm algo,
	const Mode mode,
	const Direction direction
)
	: backend(
		new SymmetricCipherGcrypt(
			algo,
			mode,
			direction
		)
	),
	initialized(
		false
	)
{
}

SymmetricCipher::~SymmetricCipher()
{
}

bool SymmetricCipher::init(
	const QByteArray &key,
	const QByteArray &iv
)
{
	if(!this->backend->init())
	{
		return false;
	}
	if(!this->backend->setKey(
		key
	))
	{
		return false;
	}
	if(!this->backend->setIv(
		iv
	))
	{
		return false;
	}
	this->initialized = true;
	return true;
}

bool SymmetricCipher::isInitalized() const
{
	return this->initialized;
}

bool SymmetricCipher::reset() const
{
	return this->backend->reset();
}

qint64 SymmetricCipher::getBlockSize() const
{
	return this->backend->getBlockSize();
}

QString SymmetricCipher::getErrorString() const
{
	return this->backend->getErrorString();
}
