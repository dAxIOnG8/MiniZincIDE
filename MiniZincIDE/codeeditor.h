#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QTabWidget>

#include "highlighter.h"

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CodeEditor(QFile& file, QFont& font, QTabWidget* tabs, QWidget *parent);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    QString filepath;
    QString filename;
    void setEditorFont(QFont& font);
protected:
    void resizeEvent(QResizeEvent *event);
    void initUI(QFont& font);
    virtual void keyPressEvent(QKeyEvent *e);
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void docChanged(bool);
    void loadContents();
private:
    QWidget* lineNumberArea;
    QWidget* loadContentsButton;
    QTabWidget* tabs;
    Highlighter* highlighter;
    int matchLeft(QTextBlock block, QChar b, int i, int n);
    int matchRight(QTextBlock block, QChar b, int i, int n);
signals:

public slots:

};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

#endif // CODEEDITOR_H
