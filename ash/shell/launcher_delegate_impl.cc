// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/shell/launcher_delegate_impl.h"

#include "ash/shell/toplevel_window.h"
#include "ash/shell/window_watcher.h"
#include "ash/wm/window_util.h"
#include "grit/ui_resources.h"
#include "ui/aura/window.h"

namespace ash {
namespace shell {

LauncherDelegateImpl::LauncherDelegateImpl(WindowWatcher* watcher)
    : watcher_(watcher) {
}

LauncherDelegateImpl::~LauncherDelegateImpl() {
}

void LauncherDelegateImpl::CreateNewTab() {
  ash::shell::ToplevelWindow::CreateParams create_params;
  create_params.can_resize = true;
  create_params.can_maximize = true;
  ash::shell::ToplevelWindow::CreateToplevelWindow(create_params);
}

void LauncherDelegateImpl::ItemClicked(const ash::LauncherItem& item) {
  aura::Window* window = watcher_->GetWindowByID(item.id);
  window->Show();
  ash::wm::ActivateWindow(window);
}

int LauncherDelegateImpl::GetBrowserShortcutResourceId() {
  return IDR_AURA_LAUNCHER_BROWSER_SHORTCUT;
}

string16 LauncherDelegateImpl::GetTitle(const ash::LauncherItem& item) {
  return watcher_->GetWindowByID(item.id)->title();
}

ui::MenuModel* LauncherDelegateImpl::CreateContextMenu(
    const ash::LauncherItem& item) {
  return NULL;
}

ash::LauncherID LauncherDelegateImpl::GetIDByWindow(aura::Window* window) {
  return watcher_->GetIDByWindow(window);
}

}  // namespace shell
}  // namespace ash
