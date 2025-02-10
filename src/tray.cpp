#include "tray.h"

Window::Window() {
    createIconGroupBox();
    setWindowTitle("Tray");
    resize(400, 300);
}

void Window::setVisible(bool visible) {
}
void Window::closeEvent(QCloseEvent* event) {
}

void Window::setIcon(int index) {
}
void Window::createIconGroupBox()
{

}