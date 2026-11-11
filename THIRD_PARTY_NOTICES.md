<div align="center">

# Third-Party Notices / 第三方声明 

[English](#english) | [中文](#中文)

</div>

---

# English

> Parts of this file are copied from and modified based on [**Deepseek Harness**](https://github.com/deepseek-ai/deepseek-harness/blob/master/THIRD_PARTY_NOTICES.md), which is licensed under the `MIT License`.  
> Its copyright notice and full license text are provided in the file linked in the ["Referenced Projects"](#referenced-projects) section at the below of this file.

SFL is licensed under [Apache License 2.0](LICENSE.txt). It depends on the third-party software listed below. Each project remains under its own license; nothing in this file changes those terms.

This file lists the third-party components that SFL includes or uses at build time, together with their license notices. It is maintained by hand. Components that are only required at runtime and are not distributed with SFL (such as GTK, WebKitGTK and the WebView2 Runtime) are listed separately at the end. Please update this file whenever a dependency is added, removed or upgraded.

## Components

| Component | Version | Source | License |
| --- | --- | --- | --- |
| webview | v0.12.0 | [github.com/webview/webview](https://github.com/webview/webview) | [MIT](license/WEBVIEW_LICENSE.txt) |
| nlohmann_json | v3.12.0 | [github.com/nlohmann/json](https://github.com/nlohmann/json) | [MIT](license/NLOHMANN_JSON_LICENSE.txt) |
| Microsoft.Web.WebView2 SDK | 1.0.4191.47 | [nuget.org](https://www.nuget.org/packages/Microsoft.Web.WebView2) | [BSD-3-Clause](license/WEBVIEW2_LICENSE.txt) |

## Runtime dependencies (not distributed with SFL)

SFL does not include or redistribute them. Links to their license texts are provided for reference only.

| Component | Platform | Source | License |
| --- | --- | --- | --- |
| GTK 3 | Linux | [gtk.org](https://www.gtk.org) | Mainly [LGPL-2.1-or-later](https://spdx.org/licenses/LGPL-2.1-or-later.html); some files under other licenses (see the package's copyright file) |
| WebKitGTK | Linux | [webkitgtk.org](https://webkitgtk.org) | Mainly [BSD-2-Clause](https://spdx.org/licenses/BSD-2-Clause.html); some files under other licenses, including LGPL (see the package's copyright file) |
| Microsoft Edge WebView2 Runtime | Windows | [developer.microsoft.com](https://developer.microsoft.com/microsoft-edge/webview2/) | Microsoft license terms |
| WebKit | macOS | [webkit.org](https://webkit.org) | System component |

<a id="referenced-projects"></a>
## Referenced Projects

Parts of this file are copied from and modified based on the project below, which is licensed under the MIT License. Its copyright notice and license text are provided unchanged in the linked file.

| Project | Source | Copied From | License |
| --- | --- | --- | --- |
| Deepseek Harness | [github.com/deepseek-ai/deepseek-harness](https://github.com/deepseek-ai/deepseek-harness) | [THIRD_PARTY_NOTICES.md](https://github.com/deepseek-ai/deepseek-harness/blob/master/THIRD_PARTY_NOTICES.md) | [MIT](license/DEEPSEEK_HARNESS_LICENSE.txt) |

---

# 中文

> 本文件的部分文字复制自 [Deepseek Harness](https://github.com/deepseek-ai/deepseek-harness/blob/master/THIRD_PARTY_NOTICES.md)(MIT 许可证),并作了修改。  
> 其版权声明和许可证全文见下方[“参考项目”](#参考项目)一节所链接的文件。

SFL 以 [Apache License 2.0](LICENSE.txt) 授权。它包含或依赖下列第三方软件,各项目仍适用其各自的许可证,本文件不改变这些条款。

本文件列出了 SFL 包含或在构建时使用的第三方组件及其许可证声明,由人工维护。仅在运行时需要、且不随 SFL 分发的组件(如 GTK、WebKitGTK 和 WebView2 Runtime)单独列在文末。新增、移除或升级依赖时,请同步更新本文件。

## 组件

| 组件 | 版本 | 来源 | 许可证 |
| --- | --- | --- | --- |
| webview | v0.12.0 | [github.com/webview/webview](https://github.com/webview/webview) | [MIT](license/WEBVIEW_LICENSE.txt) |
| nlohmann_json | v3.12.0 | [github.com/nlohmann/json](https://github.com/nlohmann/json) | [MIT](license/NLOHMANN_JSON_LICENSE.txt) |
| Microsoft.Web.WebView2 SDK | 1.0.4191.47 | [nuget.org](https://www.nuget.org/packages/Microsoft.Web.WebView2) | [BSD-3-Clause](license/WEBVIEW2_LICENSE.txt) |

## 运行时依赖(未随 SFL 分发)

SFL 不包含也不再分发它们。此处仅提供许可证文本的链接,供参考。

| 组件 | 平台 | 来源 | 许可证 |
| --- | --- | --- | --- |
| GTK 3 | Linux | [gtk.org](https://www.gtk.org) | 主要为 [LGPL-2.1-or-later](https://spdx.org/licenses/LGPL-2.1-or-later.html);部分文件适用其他许可证(见发行版包内的 copyright 文件) |
| WebKitGTK | Linux | [webkitgtk.org](https://webkitgtk.org) | 主要为 [BSD-2-Clause](https://spdx.org/licenses/BSD-2-Clause.html);部分文件适用其他许可证,包括 LGPL(见发行版包内的 copyright 文件) |
| Microsoft Edge WebView2 Runtime | Windows | [developer.microsoft.com](https://developer.microsoft.com/microsoft-edge/webview2/) | 微软许可条款 |
| WebKit | macOS | [webkit.org](https://webkit.org) | 系统组件 |

## 参考项目

本文件的部分文字复制自下列项目(MIT 许可证)并作了修改。其版权声明和许可证文本在所链接的文件中原样提供。

| 项目 | 来源 | 复制自 | 许可证 |
| --- | --- | --- | --- |
| Deepseek Harness | [github.com/deepseek-ai/deepseek-harness](https://github.com/deepseek-ai/deepseek-harness) | [THIRD_PARTY_NOTICES.md](https://github.com/deepseek-ai/deepseek-harness/blob/master/THIRD_PARTY_NOTICES.md) | [MIT](license/DEEPSEEK_HARNESS_LICENSE.txt) |