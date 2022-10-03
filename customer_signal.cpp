#include "customer_signal.h"

void cus_QLineEdit::enterEvent(QEnterEvent *event)
{
    emit mouse_enter();
}
void cus_QLineEdit::leaveEvent(QEvent* event)
{
    emit mouse_leave();
}
void cus_QLineEdit::focusInEvent(QFocusEvent *e)
{
    emit focus_in();
    return QLineEdit::focusInEvent(e);
}
void cus_QLineEdit::focusOutEvent(QFocusEvent *e)
{
    emit focus_out();
    return QLineEdit::focusOutEvent(e);
}
