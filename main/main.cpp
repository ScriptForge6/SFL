#include "webview/webview.h"

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
    w.set_html(R"111(
      <!DOCTYPE html>
<html lang="zh-CN">
<head>
    <script src="https://www.script-forge.top/head.js"></script>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>个人介绍 | 我的个人主页</title>
    <meta name="description" content="ScriptForge 的个人主页 - C/C++ 开发者，展示项目、技能与联系方式。">

    <!-- Open Graph -->
    <meta property="og:title" content="ScriptForge 的个人主页">
    <meta property="og:description" content="C/C++ 开发者，展示项目、技能与联系方式。">
    <meta property="og:type" content="website">
    <meta property="og:image" content="https://www.script-forge.top/dependency/ScriptForge.png">
    <link rel="icon" href="https://www.script-forge.top/dependency/ScriptForge.png" type="image/png">

    <!-- 引入 Tailwind CSS CDN / 本地样式 -->
    <link rel="stylesheet" href="https://www.script-forge.top/css/tailwind.min.css">

    <!-- 引入 Font-Awesome 图标库 -->
    <link href="https://www.script-forge.top/fontawesome-free-7.3.1/css/all.min.css" rel="stylesheet">

    <!-- 引入 ScriptForge 核心 CSS & JS 库 -->
    <link rel="stylesheet" href="https://cdn.script-forge.top/Scriptforge-css.css">
    

    <style>
        .hero-section > div {
            display: flex !important;
            flex-direction: column !important;
            align-items: center !important;
            justify-content: space-between !important;
            gap: 2rem !important;
        }

        @media (min-width: 768px) {
            .hero-section > div {
                flex-direction: row !important;
            }
            .hero-section > div > div:first-child {
                width: 60% !important;
            }
            .hero-section > div > div:last-child {
                width: 35% !important;
                display: flex !important;
                justify-content: flex-end !important;
            }
        }

        .hero-section {
            background: linear-gradient(135deg, rgba(0, 122, 255, 0.08) 0%, rgba(0, 122, 255, 0.02) 100%);
        }
        
        .project-card-img {
            border-top-left-radius: calc(var(--radius-card) - 1px);
            border-top-right-radius: calc(var(--radius-card) - 1px);
        }

        .sf-header-nav {
            display: flex;
            align-items: center;
            justify-content: space-between;
            width: 100%;
            max-width: 1200px;
            margin: 0 auto;
        }

        .tech-tag {
            font-size: 0.7rem;
            padding: 2px 8px;
            border-radius: 6px;
            background: rgba(0, 122, 255, 0.1);
            color: var(--bg-primary);
            font-weight: 600;
        }
    </style>
</head>
<body>
  <!-- 全局 Toast 容器组件 -->
  <sf-toast id="global-toast"></sf-toast>

  <!-- 头部菜单导航 -->
  <sf-menu>
    <a href="#" class="text-xl font-bold tracking-tight" style="color: var(--bg-primary);">
      <i class="fa fa-code mr-1"></i> ScriptForge
    </a>
    <a href="#about" class="menu-link">
      <i class="fa fa-solid fa-user-gear"></i>
      <span>关于我</span>
    </a>
    <a href="#projects" class="menu-link">
      <i class="fa fa-solid fa-cubes"></i>
      <span>核心项目</span>
    </a>
    <a href="#skills" class="menu-link">
      <i class="fa fa-solid fa-layer-group"></i>
      <span>技术栈</span>
    </a>
    <a href="#contact" class="menu-link">
      <i class="fa fa-solid fa-paper-plane"></i>
      <span>联系方式</span>
    </a>

    <div slot="right" class="flex items-center gap-3">
      <a href="https://github.com/ScriptForge666" target="_blank" class="text-gray-500 hover:text-blue-500 transition-colors text-lg" title="GitHub Profile">
        <i class="fa fa-brands fa-github"></i>
      </a>
      <div class="flex items-center gap-2 pl-2 border-l border-gray-300 dark:border-gray-700">
        <theme-button id="theme-widget" size="1.8" value=""></theme-button>
      </div>
    </div>
  </sf-menu>

  <main class="page-wrapper py-8">
    
    <section id="hero" class="py-12 md:py-16">
      <div class="card flex flex-col md:flex-row items-center justify-between gap-8 p-8 md:p-12">
        <div class="flex-1 space-y-4 text-left">
          <div class="inline-flex items-center gap-2 px-3 py-1 rounded-full text-xs font-semibold bg-blue-50 dark:bg-blue-950/60 text-blue-600 dark:text-blue-400 border border-blue-200 dark:border-blue-800">
            <span class="w-2 h-2 rounded-full bg-blue-500 animate-pulse"></span>
            C++ Systems & Windows Tooling Specialist
          </div>
          <h1>你好，我是 <span class="text-blue-500">ScriptForge</span></h1>
          <p class="text-lg leading-relaxed max-w-2xl">
            热衷于构建高效 C++ 原生应用、Windows 系统工具及现代化自动化脚本。精通 C++11~C++23、XMake 构建工具生态与 Windows API 开发。
          </p>
          <div class="flex flex-wrap items-center gap-4 pt-4">
            <a href="#projects" class="btn">
              <i class="fa-solid fa-rocket"></i> 浏览核心项目
            </a>
            <a href="#contact" class="btn btn-secondary">
              <i class="fa-regular fa-envelope"></i> 立即联系
            </a>
            <button onclick="copyQQ()" class="btn btn-secondary">
              <i class="fa-brands fa-qq"></i> QQ: 3974142081
            </button>
          </div>
        </div>
        
        <div class="relative flex items-center justify-center">
          <div class="w-36 h-36 md:w-44 md:h-44 rounded-2xl bg-gradient-to-tr from-blue-600 to-indigo-500 p-1 shadow-2xl flex items-center justify-center">
            <div class="w-full h-full bg-white dark:bg-zinc-900 rounded-xl flex flex-col items-center justify-center text-blue-500 gap-2">
              <img src="https://www.script-forge.top/dependency/ScriptForge.png" alt="ScriptForge 头像" class="w-full h-full object-cover" loading="lazy">
            </div>
          </div>
        </div>
      </div>
    </section>

    <section id="about" class="py-4">
      <div class="card">
        <h2 class="flex items-center gap-3">
          <i class="fa-solid fa-user text-blue-500"></i> 关于我
        </h2>
        <p class="mt-2 text-base leading-relaxed">
          我是 <strong>ScriptForge</strong>，一名专注于 C++ 底层开发、Windows 平台系统集成与构建自动化流程的独立开发者。
          我致力于通过现代 C++ 语言特性和简洁、高效的代码范式，打造极简、无依赖且性能优异的技术工具，帮助开发者提升开发体验与日常工作效率。
        </p>
        <div class="grid grid-cols-1 md:grid-cols-3 gap-4 mt-6">
          <div class="p-4 rounded-xl dark:bg-zinc-800/50 border border-gray-100 dark:border-zinc-800">
            <i class="fa-solid fa-bolt text-2xl text-amber-500 mb-2"></i>
            <h4 class="font-bold text-gray-900 dark:text-white">极致性能</h4>
            <p class="text-xs text-gray-500 dark:text-gray-400 mt-1">追求高性能 C++ 代码实现，极小的二进制体积与内存占用。</p>
          </div>
          <div class="p-4 rounded-xl dark:bg-zinc-800/50 border border-gray-100 dark:border-zinc-800">
            <i class="fa-solid fa-gears text-2xl text-blue-500 mb-2"></i>
            <h4 class="font-bold text-gray-900 dark:text-white">工程自动化</h4>
            <p class="text-xs text-gray-500 dark:text-gray-400 mt-1">深耕 XMake、CMake 及 PowerShell 自动化构建与终端体验改良。</p>
          </div>
          <div class="p-4 rounded-xl dark:bg-zinc-800/50 border border-gray-100 dark:border-zinc-800">
            <i class="fa-brands fa-windows text-2xl text-cyan-500 mb-2"></i>
            <h4 class="font-bold text-gray-900 dark:text-white">Win32 原生集成</h4>
            <p class="text-xs text-gray-500 dark:text-gray-400 mt-1">精通 Win32/COM API 与 Windows 10/11 系统的原生交互与调优。</p>
          </div>
        </div>
      </div>
    </section>

    <section id="projects" class="py-6">
      <div class="flex flex-col sm:flex-row sm:items-center justify-between gap-2 mb-4 px-1">
  <h2><i class="fa-solid fa-folder-open text-blue-500"></i> 代表开源项目</h2>
  
  <div class="flex items-center gap-2">
    <!-- 个人主页按钮 -->
    <a href="https://github.com/ScriptForge666?tab=repositories" target="_blank" 
       class="btn btn-secondary !py-1 !px-2.5 !text-xs inline-flex items-center gap-1.5">
      <i class="fa-solid fa-user text-xs"></i> 个人仓库
    </a>
    
    <!-- 组织主页按钮 -->
    <a href="https://github.com/orgs/ScriptForge6/repositories" target="_blank" 
       class="btn btn-secondary !py-1 !px-2.5 !text-xs inline-flex items-center gap-1.5">
      <i class="fa-solid fa-building text-xs"></i> 组织仓库
    </a>
  </div>
</div>

      <div class="grid grid-cols-1 md:grid-cols-2 gap-6">
        
        <!-- Project 1 -->
        <div class="card flex flex-col justify-between">
          <div>
            <div class="flex items-start justify-between gap-3 mb-2">
              <h3 class="text-lg font-bold text-gray-900 dark:text-white flex items-center gap-2">
                <i class="fa-solid fa-screwdriver-wrench text-blue-500"></i>
                Scriptforge-xmake
              </h3>
              <a href="https://github.com/ScriptForge6/Scriptforge-xmake" target="_blank" class="text-gray-400 hover:text-blue-500 transition-colors text-lg" title="GitHub Repo">
                <i class="fa-brands fa-github"></i>
              </a>
            </div>
            <p class="text-sm mb-4">
              轻量高效的 C++ 项目模板与 XMake 构建集成生态。旨在极大地简化 Modern C++ 项目工程初始化与跨平台工程依赖管理。
            </p>
            <ul class="text-xs space-y-1.5 text-gray-500 dark:text-gray-400 mb-4 list-disc list-inside">
              <li>开箱即用的现代化 C++ 工程结构设计</li>
              <li>开箱无缝集成 XMake，秒级配置编译链</li>
              <li>优化构建选项与二进制输出目录组织</li>
            </ul>
          </div>
          <div class="flex flex-wrap gap-2 pt-2 border-t border-gray-100 dark:border-zinc-800">
            <span class="tech-tag">C++</span>
            <span class="tech-tag">XMake</span>
            <span class="tech-tag">CMake</span>
            <span class="tech-tag">Build System</span>
          </div>
        </div>

        <!-- Project 2 -->
        <div class="card flex flex-col justify-between">
          <div>
            <div class="flex items-start justify-between gap-3 mb-2">
              <h3 class="text-lg font-bold text-gray-900 dark:text-white flex items-center gap-2">
                <i class="fa-solid fa-terminal text-emerald-500"></i>
                Add-VsDevPwsh7
              </h3>
              <a href="https://github.com/ScriptForge6/Add-VsDevPwsh7" target="_blank" class="text-gray-400 hover:text-blue-500 transition-colors text-lg" title="GitHub Repo">
                <i class="fa-brands fa-github"></i>
              </a>
            </div>
            <p class="text-sm mb-4">
              Auto PS5.1 自动化脚本：为 Visual Studio 启用 PowerShell 7 开发者终端（专为 Win10/Win11 打造）。
            </p>
            <ul class="text-xs space-y-1.5 text-gray-500 dark:text-gray-400 mb-4 list-disc list-inside">
              <li>自动读取并环境匹配 VS 开发人员环境</li>
              <li>无缝提升 Visual Studio 终端至 PS 7.x 体验</li>
              <li>全自动化配置体验，支持防重复清理机制</li>
            </ul>
          </div>
          <div class="flex flex-wrap gap-2 pt-2 border-t border-gray-100 dark:border-zinc-800">
            <span class="tech-tag">PowerShell 7</span>
            <span class="tech-tag">Visual Studio</span>
            <span class="tech-tag">Win10/11</span>
            <span class="tech-tag">Automation</span>
          </div>
        </div>

        <!-- Project 3 -->
        <div class="card flex flex-col justify-between">
          <div>
            <div class="flex items-start justify-between gap-3 mb-2">
              <h3 class="text-lg font-bold text-gray-900 dark:text-white flex items-center gap-2">
                <i class="fa-solid fa-eye-slash text-purple-500"></i>
                HideWindow
              </h3>
              <a href="https://github.com/ScriptForge6/HideWindow" target="_blank" class="text-gray-400 hover:text-blue-500 transition-colors text-lg" title="GitHub Repo">
                <i class="fa-brands fa-github"></i>
              </a>
            </div>
            <p class="text-sm mb-4">
              基于 Win32 API 打造的高效轻量 C++ 原生小工具，用于后台静默隐藏、最小化或全局管理活跃的应用程序窗口。
            </p>
            <ul class="text-xs space-y-1.5 text-gray-500 dark:text-gray-400 mb-4 list-disc list-inside">
              <li>直接调用 Windows Native API，零额外运行时依赖</li>
              <li>极低 CPU 与内存开销，支持快捷键静默控制</li>
              <li>灵活匹配句柄、类名或进程名进行精准隐藏操作</li>
            </ul>
          </div>
          <div class="flex flex-wrap gap-2 pt-2 border-t border-gray-100 dark:border-zinc-800">
            <span class="tech-tag">C++</span>
            <span class="tech-tag">Win32 API</span>
            <span class="tech-tag">Windows Tool</span>
            <span class="tech-tag">System</span>
          </div>
        </div>

        <!-- Project 4 -->
        <div class="card flex flex-col justify-between">
          <div>
            <div class="flex items-start justify-between gap-3 mb-2">
              <h3 class="text-lg font-bold text-gray-900 dark:text-white flex items-center gap-2">
                <i class="fa-solid fa-vial text-rose-500"></i>
                sf_test
              </h3>
              <a href="https://github.com/ScriptForge6/sf_test" target="_blank" class="text-gray-400 hover:text-blue-500 transition-colors text-lg" title="GitHub Repo">
                <i class="fa-brands fa-github"></i>
              </a>
            </div>
            <p class="text-sm mb-4">
              专为 Xmake 制作的轻量测试模块，可以支持自动运行 GTest 测试框架测试，摆脱 XMake 只支持测试自己的 test 而不支持运行 GTest 的烦恼。
            </p>
            <ul class="text-xs space-y-1.5 text-gray-500 dark:text-gray-400 mb-4 list-disc list-inside">
              <li>安装即使用，无需复杂配置</li>
              <li>支持使用命令行选择性运行 GTest 测试，节省测试使用时间</li>
              <li>与 Xmake 生态无缝集成，简化测试流程</li>
            </ul>
          </div>
          <div class="flex flex-wrap gap-2 pt-2 border-t border-gray-100 dark:border-zinc-800">
            <span class="tech-tag">C++</span>
            <span class="tech-tag">GTest</span>
            <span class="tech-tag">XMake</span>
            <span class="tech-tag">Framework</span>
          </div>
        </div>

      </div>
    </section>

    <section id="skills" class="py-6">
      <div class="card">
        <h2><i class="fa-solid fa-layer-group text-blue-500"></i> 技术栈与专业技能</h2>
        <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-4 mt-4">
          
          <div class="p-4 rounded-xl dark:bg-zinc-800/40 border border-gray-100 dark:border-zinc-800">
            <h4 class="text-sm font-bold text-blue-500 mb-2 flex items-center gap-2">
              <i class="fa-solid fa-code"></i> C++ 语言核心
            </h4>
            <ul class="text-xs space-y-2 text-gray-600 dark:text-gray-300">
              <li>• C++11 / C++17 / C++20 / C++23</li>
              <li>• Win32 / COM API 系统编程</li>
              <li>• STL 与泛型编程实践</li>
              <li>• 内存管理与性能调优</li>
            </ul>
          </div>

          <div class="p-4 rounded-xl dark:bg-zinc-800/40 border border-gray-100 dark:border-zinc-800">
            <h4 class="text-sm font-bold text-blue-500 mb-2 flex items-center gap-2">
              <i class="fa-solid fa-hammer"></i> 构建工具与自动化
            </h4>
            <ul class="text-xs space-y-2 text-gray-600 dark:text-gray-300">
              <li>• XMake 自动化生态搭建</li>
              <li>• CMake 构建脚本编写</li>
              <li>• Visual Studio MSBuild 链</li>
              <li>• CI/CD 自动化构建流程</li>
            </ul>
          </div>

          <div class="p-4 rounded-xl dark:bg-zinc-800/40 border border-gray-100 dark:border-zinc-800">
            <h4 class="text-sm font-bold text-blue-500 mb-2 flex items-center gap-2">
              <i class="fa-solid fa-terminal"></i> 脚本与终端集成
            </h4>
            <ul class="text-xs space-y-2 text-gray-600 dark:text-gray-300">
              <li>• PowerShell 7 & 5.1 自动化</li>
              <li>• Windows CMD / Batch 脚本</li>
              <li>• Shell / Linux 部署脚本</li>
              <li>• VS Code & VS 终端增强</li>
            </ul>
          </div>

          <div class="p-4 rounded-xl dark:bg-zinc-800/40 border border-gray-100 dark:border-zinc-800">
            <h4 class="text-sm font-bold text-blue-500 mb-2 flex items-center gap-2">
              <i class="fa-solid fa-palette"></i> Web 体验与工具
            </h4>
            <ul class="text-xs space-y-2 text-gray-600 dark:text-gray-300">
              <li>• HTML5 / CSS3 / JavaScript</li>
              <li>• Tailwind CSS & 现代化UI</li>
              <li>• Web Components 封装</li>
              <li>• Git 体系与开源协作</li>
            </ul>
          </div>

        </div>
      </div>
    </section>

    <section id="contact" class="py-6">
      <div class="grid grid-cols-1 md:grid-cols-3 gap-6">
        
        <!-- Contact Cards -->
        <div class="space-y-4 md:col-span-1">
          <div class="card !mb-0 p-5">
            <h3 class="text-base font-bold mb-3"><i class="fa-solid fa-address-card text-blue-500"></i> 联系与交流</h3>
            <div class="space-y-3">
              
              <div onclick="copyQQ()" class="p-3 rounded-lg dark:bg-zinc-800/60 hover:bg-blue-50 dark:hover:bg-blue-950/40 border border-gray-200 dark:border-zinc-700/50 cursor-pointer transition-all flex items-center justify-between group">
                <div class="flex items-center gap-3">
                  <div class="w-9 h-9 rounded-full bg-blue-500 text-white flex items-center justify-center text-sm">
                    <i class="fa-brands fa-qq"></i>
                  </div>
                  <div>
                    <div class="text-xs text-gray-400">QQ 号码</div>
                    <div class="font-mono text-sm font-bold">3974142081</div>
                  </div>
                </div>
                <i class="fa-regular fa-copy text-gray-400 group-hover:text-blue-500 text-xs"></i>
              </div>

              <a href="mailto:scriptforge@outlook.com" onclick="copyEmail()" class="p-3 rounded-lg dark:bg-zinc-800/60 hover:bg-blue-50 dark:hover:bg-blue-950/40 border border-gray-200 dark:border-zinc-700/50 cursor-pointer transition-all flex items-center justify-between group block">
                <div class="flex items-center gap-3">
                  <div class="w-9 h-9 rounded-full bg-indigo-500 text-white flex items-center justify-center text-sm">
                    <i class="fa-regular fa-envelope"></i>
                  </div>
                  <div>
                    <div class="text-xs text-gray-400">电子邮件</div>
                    <div class="font-mono text-sm font-bold truncate max-w-[150px]">scriptforge@outlook.com</div>
                  </div>
                </div>
                <i class="fa-regular fa-copy text-gray-400 group-hover:text-blue-500 text-xs"></i>
              </a>

              <a href="https://github.com/ScriptForge666" target="_blank" class="p-3 rounded-lg dark:bg-zinc-800/60 hover:bg-blue-50 dark:hover:bg-blue-950/40 border border-gray-200 dark:border-zinc-700/50 cursor-pointer transition-all flex items-center justify-between group block">
                <div class="flex items-center gap-3">
                  <div class="w-9 h-9 rounded-full bg-gray-800 text-white flex items-center justify-center text-sm">
                    <i class="fa-brands fa-github"></i>
                  </div>
                  <div>
                    <div class="text-xs text-gray-400">GitHub 主页</div>
                    <div class="font-mono text-sm font-bold">ScriptForge666</div>
                  </div>
                </div>
                <i class="fa-solid fa-arrow-up-right-from-square text-gray-400 group-hover:text-blue-500 text-xs"></i>
              </a>

            </div>
          </div>
        </div>

        <!-- Form Card -->
        
        <div class="card md:col-span-2 !mb-0">
          <h3 class="text-base font-bold mb-1"><i class="fa-solid fa-paper-plane text-blue-500"></i> 发送留言消息</h3>
          <p class="text-xs text-gray-500 mb-4">有项目合作意向、技术交流或 Bug 反馈？随时给我留言。</p>
          
          <form id="contact-form" class="space-y-2">
            <div class="grid grid-cols-1 sm:grid-cols-2 gap-3">
              <div>
                <label class="text-xs font-semibold text-gray-600 dark:text-gray-400">您的称呼 / 昵称</label>
                <input type="text" id="sender-name" placeholder="例如：Developer" required />
              </div>
              <div>
                <label class="text-xs font-semibold text-gray-600 dark:text-gray-400">联系邮箱 / 联系方式</label>
                <input type="email" id="sender-contact" placeholder="例如：your-email@example.com" required />
              </div>
            </div>
            <div>
              <label class="text-xs font-semibold text-gray-600 dark:text-gray-400">留言主题</label>
              <input type="text" id="msg-subject" placeholder="项目合作 / 技术探讨 / 其他" required />
            </div>
            <div>
              <label class="text-xs font-semibold text-gray-600 dark:text-gray-400">详细留言内容</label>
              <textarea id="msg-body" rows="3" placeholder="请输入您想要交流的具体内容..." required></textarea>
            </div>
            <button type="submit" class="btn w-full sm:w-auto">
              <i class="fa-solid fa-paper-plane"></i> 提交留言信息
            </button>
          </form>
        </div>
        

      </div>
    </section>
  </main>

  <!-- Footer -->
  <footer class="py-8 text-center text-xs text-gray-400 border-t border-gray-200 dark:border-zinc-800/80 mt-12">
    <p>© 2026 ScriptForge. Licensed under the Apache2.0 License.</p>
  </footer>
  <script src="https://www.script-forge.top/Day-night-toggle-button/script.js"></script>
  <script src="https://cdn.script-forge.top/Scriptforge-js.js"></script>
  <script src="https://www.script-forge.top/toggle-theme.js"></script>
  <script>

    // 复制 QQ 号
    function copyQQ() {
      const qq = "3974142081";
      copyToClipboard(qq);
      showToastNotification("QQ号码已成功复制: " + qq);
    }

    // 复制 邮箱
    function copyEmail() {
      const email = "scriptforge@outlook.com";
      copyToClipboard(email);
      showToastNotification("邮箱地址已复制: " + email);
    }

    // 复制剪贴板通用函数
    function copyToClipboard(text) {
      if (navigator.clipboard && window.isSecureContext) {
        navigator.clipboard.writeText(text);
      } else {
        const textArea = document.createElement("textarea");
        textArea.value = text;
        textArea.style.position = "fixed";
        textArea.style.left = "-999999px";
        document.body.appendChild(textArea);
        textArea.focus();
        textArea.select();
        try {
          document.execCommand('copy');
        } catch (error) {
          console.error("Copy failed", error);
        }
        document.body.removeChild(textArea);
      }
    }

    // 显示 Toast 提示
    function showToastNotification(msg) {
      const toastComp = document.getElementById('global-toast');
      if (toastComp && toastComp.showToast) {
        toastComp.showToast(msg);
      }
    }

    async function getIp() {
    try {
        const res = await fetch("/api/ip");
        const data = await res.json();
        return data; // 返回完整 {ip,country,city...} 对象
    } catch (err) {
        console.error("获取 IP 地址失败:", err);
        // 出错兜底，防止访问属性报错
        return { 
            ip: "未知",
            country: "未知",
            continent: "未知",
            region: "未知",
            regionCode: 0,
            city: "未知",
            timezone: "未知",
            asn: "未知"
        };
    }
}

    // 处理 Cloudflare Pages / API 表单提交
    document.getElementById('contact-form')?.addEventListener('submit', async (e) => {
        e.preventDefault();
        const form = e.target;
        const submitBtn = form.querySelector('button[type="submit"]');

        const ip = await getIp();

        submitBtn.disabled = true;
        const data = {
            name: document.getElementById('sender-name').value,
            contact: document.getElementById('sender-contact').value,
            subject: document.getElementById('msg-subject').value,
            message: document.getElementById('msg-body').value,
            ip: ip.ip,
            country: ip.country,
            region: ip.region,
            city: ip.city
        };
        try {
            const res = await fetch('/api/submit', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(data)
            });
            const result = await res.json();
            if (res.ok && result.success) {
                showToastNotification('消息已成功发送！');
                form.reset();
            } else {
                // 读取后端返回的错误信息展示给用户
                showToastNotification(`提交失败：${result.error || '服务器异常'}`);
            }
        } catch (err) {
            // 区分：网络/CORS错误，明确告诉用户失败，不要伪装成功
            console.error('表单提交异常:', err);
            showToastNotification('提交失败：网络异常或跨域访问被拒绝');
        } finally {
            submitBtn.disabled = false;
        }
    });

    // 页面加载完成后触发卡片渐次显现动画
    window.addEventListener('DOMContentLoaded', () => {
      if (typeof revealCardsSequentially === 'function') {
        revealCardsSequentially(100);
      }
    });
  </script>
</body>
</html>
    )111");
    w.run();
  } catch (const webview::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}