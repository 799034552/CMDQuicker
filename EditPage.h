#ifndef EDITPAGE_H
#define EDITPAGE_H
#include "SlidePage.h"
#include "InputBox.h"
#include "cmd.h"
#include <vector>
class EditPage : public SlidePage
{
    Q_OBJECT
public:
    EditPage(const QString &title, QWidget *parent);
    void set_contain(QString title, QString contain, QWidget *w=nullptr);
    virtual void slide_in(bool is_max=false, QString title = "", QString contain = "", QWidget *w=nullptr);
private:
    InputBox *input_box = nullptr;
    QTextEdit *editor = nullptr;
    QWidget *editing_w = nullptr;
signals:
    void add_commit();
    void edit_commit (QWidget *w, std::vector<string> v);
};

#endif // EDITPAGE_H
