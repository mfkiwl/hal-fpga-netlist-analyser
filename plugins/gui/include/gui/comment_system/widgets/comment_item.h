//  MIT License
//
//  Copyright (c) 2019 Ruhr University Bochum, Chair for Embedded Security. All Rights reserved.
//  Copyright (c) 2021 Max Planck Institute for Security and Privacy. All Rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#pragma once

#include <QFrame>


class QVBoxLayout;
class QHBoxLayout;
class QToolBar;
class QLabel;
class QAction;
class QToolButton;

namespace hal
{
    class CommentEntry;

    class CommentItem : public QFrame
    {
        Q_OBJECT
    public:
        CommentItem(QWidget* parent = nullptr);
        CommentItem(CommentEntry* entry, QWidget* parent = nullptr);
        ~CommentItem();

        void setComment(CommentEntry* entry);
        void updateCurrentEntry();

    private:
        QVBoxLayout* mLayout;
        CommentEntry* mEntry;

        // header part (perhaps no toolbar but a layout with toolbuttons instead of actions?)
        QToolBar* mTopToolbar;
        QLabel* mHeader;
        QLabel* mCreationDate;
        QAction* mModifyAction;
        QAction* mDeleteAction;

        // header part v2
        QWidget* mTopWidget;
        QHBoxLayout* mTopLayout;
        QToolButton* mModifyButton;
        QToolButton* mDeleteButton;

        //This can either be an QLabel or an QTextEdit / QPlainTextEdit (TODO: decide...)
        QLabel* mText;

        void init();
        void initV2();
    };
}
