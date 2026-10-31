#include <webview/webview.h>

#include <iostream>

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main() {
#endif
  try {
    webview::webview w(false, nullptr);
    w.set_title("这只是一个占位的HTML");
    w.set_size(480, 320, WEBVIEW_HINT_NONE);
    w.set_html(R"(<h1>Hello, World!</h1>)");
    w.run();
  } catch (const webview::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}