//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHEXCEPTION_H
#define JAHEXCEPTION_H

#include <QException>

/**
 * @brief The JahException class
 *  minimal error reporting, thread safe
 */
class JahException : public QException
{
public:

    /**
     * @brief JahException
     *  define an error message handler
     * @param message
     *  user message
     */
    JahException(QString message);

    /**
     * @brief JahException
     *  copy the message
     * @param other
     *  message definition
     */
    JahException(const JahException &other);

    /** required to be thread safe */
    void raise() const { throw *this; }

    /** required to be thread safe */
    JahException *clone() const { return new JahException(*this); }

    /** user message */
    QString message;
};

#endif // JAHEXCEPTION_H
