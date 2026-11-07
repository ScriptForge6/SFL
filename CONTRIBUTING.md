# Contributing Guide / 贡献指南

[English](#english) | [中文](#中文)

---

# English

Thank you for your interest in contributing to SFL!

## Development Environment

- Compiler: C++20 support required (MSVC 2022+ / GCC 11+ / Clang 15+)
- Build tool: xmake
- Build command: `xmake`
- Platforms: Windows / Linux / macOS

> Alternatively, you can fork this repository and build it with the compile GitHub Action.

## Submission Workflow

1. Fork this repository and create your branch from `dev`.
2. Make your changes. Make sure `xmake` builds successfully without introducing new warnings (the compile GitHub Action check on your PR must pass).
3. Open a Pull Request against `dev`, explaining what you changed and why.
4. One PR should do one thing only.

## Code Style

### Naming

| Kind | Style | Example |
|---|---|---|
| Classes, structs | PascalCase | `Lang` |
| Regular functions, member functions | camelCase | `getDir` |
| Callbacks / hooks (called by other classes or frameworks) | PascalCase | `GuardConstructor` |
| Member variables | `m_` + camelCase | `m_langCode` |
| Macros | `SFL_` prefix + UPPER_CASE | `SFL_NODISCARD` |

### Conventions

- Use trailing return types: `auto foo() const -> bool`
- Mark query-style functions with `SFL_NODISCARD`
- Use macros such as `SFL_START` / `SFL_END` for namespaces
- Write default arguments only in the header declaration
- Every file starts with the Apache-2.0 license header and a Doxygen `@file` comment
- Public functions should document `@brief`, `@param` and `@return`

### Error Handling

- In the `Lang` module, use `failRuntime` / `failSystem`; they automatically attach `file:line`
- Error handling for other modules is yet to be decided
- Do not `throw` exceptions directly without location information

### TODO Comments

- Format: `// TODO: description` or `/* TODO: description */`
- Use a comment for reminders only; use the `SFL_TODO(msg)` macro where reaching that code must raise an error
- Use `Find-Todo.ps1` to list them. On Linux / macOS, run it with `pwsh` (PowerShell 7) or simply use `grep -rn "TODO:" .`

## Commit Messages

Suggested format: `type: short description`, e.g. `fix: crash when the language file is missing`

Common types: `feat`, `fix`, `docs`, `refactor`, `chore`

## Reporting Issues

Please include: operating system, steps to reproduce, expected result, actual result, and relevant logs.

## License

By submitting code, you agree to license your contribution under the Apache License 2.0.

---

# 中文

感谢你愿意参与 SFL!

## 开发环境

- 编译器:支持 C++20(MSVC 2022+ / GCC 11+ / Clang 15+)
- 构建工具:xmake
- 构建:`xmake`
- 平台:Windows / Linux / macOS

> 当然,你也可以 fork 本项目,使用 compile GitHub Action 编译。

## 提交流程

1. Fork 本仓库,从 `dev` 分支创建你的分支
2. 修改代码,确保 `xmake` 能编译通过,且不新增警告(PR 的 compile GitHub Action 检查需通过)
3. 提交 Pull Request 到 `dev` 分支,说明改了什么、为什么改
4. 一个 PR 只做一件事

## 代码风格

### 命名

| 类型 | 风格 | 例子 |
|---|---|---|
| 类、结构体 | 大驼峰 | `Lang` |
| 普通函数、成员函数 | 小驼峰 | `getDir` |
| 回调/钩子(供其他类或框架调用) | 大驼峰 | `GuardConstructor` |
| 成员变量 | `m_` + 小驼峰 | `m_langCode` |
| 宏 | `SFL_` 前缀 + 大写 | `SFL_NODISCARD` |

### 写法约定

- 函数使用尾置返回类型:`auto foo() const -> bool`
- 查询类函数标 `SFL_NODISCARD`
- 命名空间使用 `SFL_START` / `SFL_END` 等宏
- 默认参数只写在头文件的声明里
- 每个文件顶部带 Apache-2.0 版权头和 Doxygen 的 `@file` 注释
- 公开函数写 `@brief`、`@param`、`@return`

### 错误处理

- 在 `Lang` 模块中使用 `failRuntime` / `failSystem`,它们会自动附带 `文件名:行号`
- 其余错误处理方法待定
- 不要直接 `throw` 不带位置信息的异常

### TODO 注释

- 格式:`// TODO: 说明` 或 `/* TODO: 说明 */`
- 仅作提醒的用注释;运行到该处必须报错的用 `SFL_TODO(msg)` 宏
- 可用 `Find-Todo.ps1` 汇总查找;Linux / macOS 可使用 `pwsh`(PowerShell 7)运行,或直接 `grep -rn "TODO:" .`

## 提交信息

建议格式:`类型: 简短说明`,例如 `fix: 修复语言文件找不到时的崩溃`

常用类型:`feat`、`fix`、`docs`、`refactor`、`chore`

## 报告问题

提交 Issue 时请附上:操作系统、复现步骤、预期结果和实际结果、相关日志。

## 许可证

提交代码即表示你同意以 Apache License 2.0 授权你的贡献。