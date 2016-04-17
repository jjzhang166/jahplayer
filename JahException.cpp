//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahException.h"

JahException::JahException(QString message) : message(message) {
}
JahException::JahException(const JahException &other) : message(other.message) {
}
