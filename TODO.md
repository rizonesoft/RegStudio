# RegStudio TODO

> A bare-metal Windows Registry Editor built with C++23 and Native Win32 API.

---

## Phase 0: GitHub Repository Setup

- [x] Create GitHub repository `rizonesoft/RegStudio`
- [x] Add `.gitignore` for C++/CMake projects
- [x] Add `LICENSE` file (MIT or your preferred license)
- [x] Create initial `README.md` with project overview
- [x] Push initial commit

---

## Phase 1: Project Structure

- [x] Create `CMakeLists.txt` (root)
- [x] Create `src/` directory
- [x] Create `src/main.cpp` (empty entry point stub)
- [x] Create `src/ui/` directory
- [x] Create `src/core/` directory
- [x] Create `resources/` directory
- [x] Create `resources/resource.rc` (empty stub)
- [x] Create `resources/app.manifest`
- [x] Add placeholder `resources/icon.ico`

---

## Phase 2: Build System (CMake + Ninja)

- [ ] Configure CMake minimum version (3.25+)
- [ ] Set C++23 standard
- [ ] Add source file globbing
- [ ] Configure resource compilation (.rc)
- [ ] Add `-municode` compile flag (Unicode entry point)
- [ ] Add `-O3 -Wall` compile flags
- [ ] Add static linking flags (`-static -static-libgcc -static-libstdc++`)
- [ ] Link `comctl32` (Common Controls)
- [ ] Link `shlwapi` (Shell helpers)
- [ ] Link `dwmapi` (DWM API)
- [ ] Link `uxtheme` (Visual Styles)
- [ ] Link `advapi32` (Registry API)
- [ ] Verify clean build with Ninja
- [ ] Verify output `.exe` runs without MinGW DLL dependencies

---

## Phase 3: Application Manifest

- [ ] Add Common Controls v6 dependency
- [ ] Add `requireAdministrator` execution level
- [ ] Embed manifest in `resource.rc`
- [ ] Verify UAC prompt appears on launch
- [ ] Verify visual styles are active (non-Win95 look)

---

## Phase 4: Entry Point & Message Loop

- [ ] Implement `wWinMain` entry point
- [ ] Initialize Common Controls (`InitCommonControlsEx`)
- [ ] Create main window class (`WNDCLASSEXW`)
- [ ] Register window class
- [ ] Create main window (`CreateWindowExW`)
- [ ] Implement message loop (`GetMessage`, `TranslateMessage`, `DispatchMessage`)
- [ ] Handle `WM_DESTROY` → `PostQuitMessage`
- [ ] Verify empty window appears

---

## Phase 5: Main Window UI

### Window Chrome
- [ ] Set window title to "RegStudio"
- [ ] Set window icon (from resources)
- [ ] Apply dark title bar (`DwmSetWindowAttribute` DWMWA_USE_IMMERSIVE_DARK_MODE)

### Layout
- [ ] Create splitter/resizable panes (left/right)
- [ ] Handle `WM_SIZE` for child window resizing
- [ ] Store pane width ratio on resize

### Menu Bar
- [ ] Create menu resource (`IDR_MAINMENU`)
- [ ] File menu: Exit
- [ ] Edit menu: Find, Copy, Paste
- [ ] View menu: Refresh
- [ ] Help menu: About

---

## Phase 6: TreeView (Registry Hive Browser)

### Control Setup
- [ ] Create `SysTreeView32` control
- [ ] Apply `SetWindowTheme(hTree, L"Explorer", NULL)`
- [ ] Enable double-buffering (`TVS_EX_DOUBLEBUFFER`)
- [ ] Add `TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT`

### Root Nodes
- [ ] Add `HKEY_CLASSES_ROOT` node
- [ ] Add `HKEY_CURRENT_USER` node
- [ ] Add `HKEY_LOCAL_MACHINE` node
- [ ] Add `HKEY_USERS` node
- [ ] Add `HKEY_CURRENT_CONFIG` node

### Lazy Loading
- [ ] Handle `TVN_ITEMEXPANDING` notification
- [ ] Enumerate subkeys on expand (`RegEnumKeyExW`)
- [ ] Insert child nodes dynamically
- [ ] Add dummy child for expandable nodes
- [ ] Remove dummy child after real children loaded

---

## Phase 7: ListView (Value Display)

### Control Setup
- [ ] Create `SysListView32` control
- [ ] Apply `SetWindowTheme(hList, L"Explorer", NULL)`
- [ ] Set `LVS_REPORT | LVS_OWNERDATA` styles
- [ ] Enable double-buffering (`LVS_EX_DOUBLEBUFFERED`)
- [ ] Enable full-row select (`LVS_EX_FULLROWSELECT`)

### Columns
- [ ] Add "Name" column
- [ ] Add "Type" column (REG_SZ, REG_DWORD, etc.)
- [ ] Add "Data" column

### Virtual Mode
- [ ] Handle `LVN_GETDISPINFO` notification
- [ ] Implement value cache/backend vector
- [ ] Set item count with `ListView_SetItemCount`

---

## Phase 8: Registry Core Engine

### RAII Wrappers
- [ ] Create `ScopedHKey` smart pointer
- [ ] Implement `KeyDeleter` for `RegCloseKey`
- [ ] Create `OpenKey()` helper function

### Key Operations
- [ ] Implement `EnumerateSubKeys(HKEY, path)` → `std::vector<std::wstring>`
- [ ] Implement `EnumerateValues(HKEY, path)` → value info structs
- [ ] Implement `ReadValue(HKEY, path, name)` → variant data
- [ ] Handle key access errors gracefully

### Value Types
- [ ] Parse `REG_SZ` (string)
- [ ] Parse `REG_EXPAND_SZ` (expandable string)
- [ ] Parse `REG_MULTI_SZ` (multi-string)
- [ ] Parse `REG_DWORD` (32-bit integer)
- [ ] Parse `REG_QWORD` (64-bit integer)
- [ ] Parse `REG_BINARY` (binary data)

---

## Phase 9: Tree ↔ List Integration

- [ ] Handle `TVN_SELCHANGED` notification
- [ ] Get selected key path from tree
- [ ] Call `EnumerateValues()` for selected key
- [ ] Populate ListView with values
- [ ] Clear ListView on tree selection change

---

## Phase 10: Value Editing

### String Editor
- [ ] Create edit dialog for REG_SZ
- [ ] Handle REG_EXPAND_SZ editing
- [ ] Handle REG_MULTI_SZ (multiline editor)

### DWORD Editor
- [ ] Create edit dialog for REG_DWORD
- [ ] Support decimal input
- [ ] Support hexadecimal input
- [ ] Toggle between dec/hex display

### Binary/Hex Editor
- [ ] Create `IDD_HEX` dialog resource
- [ ] Implement hex byte grid display
- [ ] Implement ASCII sidebar
- [ ] Handle byte editing
- [ ] Handle copy/paste

---

## Phase 11: Key/Value Operations

### Create
- [ ] Create new key dialog
- [ ] Create new string value
- [ ] Create new DWORD value
- [ ] Create new binary value

### Delete
- [ ] Delete selected value
- [ ] Delete selected key (recursive)
- [ ] Add confirmation dialog

### Rename
- [ ] Rename selected key
- [ ] Rename selected value

### Copy/Paste
- [ ] Copy key path to clipboard
- [ ] Copy value data to clipboard

---

## Phase 12: Search

- [ ] Create search dialog (`IDD_SEARCH`)
- [ ] Search by key name
- [ ] Search by value name
- [ ] Search by value data
- [ ] Run search in `std::jthread` (background)
- [ ] Display progress indicator
- [ ] Navigate to result on selection
- [ ] Find next functionality (F3)

---

## Phase 13: Security & Privileges

### Backup Privilege
- [ ] Implement `EnablePrivilege(SE_BACKUP_NAME)`
- [ ] Use `OpenProcessToken`
- [ ] Use `LookupPrivilegeValue`
- [ ] Use `AdjustTokenPrivileges`

### Restore Privilege
- [ ] Implement `EnablePrivilege(SE_RESTORE_NAME)`

### Permission Display
- [ ] Show key permissions in status bar
- [ ] Handle access denied gracefully

---

## Phase 14: Backup & Restore

### Export
- [ ] Export key to `.reg` file (text format)
- [ ] Export key to binary hive format
- [ ] Save file dialog integration

### Import
- [ ] Import `.reg` file
- [ ] Parse REG file format
- [ ] Open file dialog integration

---

## Phase 15: Polish & UX

### Status Bar
- [ ] Create status bar control
- [ ] Show current key path
- [ ] Show value count
- [ ] Show last error message

### Keyboard Shortcuts
- [ ] F5 → Refresh
- [ ] F3 → Find Next
- [ ] Ctrl+F → Find
- [ ] Delete → Delete selected
- [ ] F2 → Rename

### Context Menus
- [ ] TreeView right-click menu
- [ ] ListView right-click menu

### Dark Mode
- [ ] Detect system dark mode preference
- [ ] Apply dark colors to client area
- [ ] Apply dark title bar
- [ ] Handle `WM_SETTINGCHANGE` for theme switch

---

## Phase 16: Testing

- [ ] Test on Windows 10 (21H2+)
- [ ] Test on Windows 11
- [ ] Test without admin rights (verify UAC prompt)
- [ ] Test large key enumeration (HKCR\CLSID)
- [ ] Test binary value editing
- [ ] Test search across large hives
- [ ] Test export/import round-trip

---

## Phase 17: Release Preparation

- [ ] Update `README.md` with features
- [ ] Add screenshots to README
- [ ] Create `CHANGELOG.md`
- [ ] Configure GitHub Actions for CI build
- [ ] Create release build configuration
- [ ] Sign executable (optional: code signing cert)
- [ ] Create GitHub Release with `.exe`

---

## Phase 18: Production

- [ ] Tag `v1.0.0` release
- [ ] Upload release binary
- [ ] Announce release
- [ ] Monitor issues for critical bugs

---

## Future Enhancements (Backlog)

- [ ] Compare two registry keys
- [ ] Bookmarks/favorites for keys
- [ ] History of visited keys
- [ ] Jump to GUID (CLSID lookup)
- [ ] ARM64 build support
- [ ] Portable settings (no registry ironically)
