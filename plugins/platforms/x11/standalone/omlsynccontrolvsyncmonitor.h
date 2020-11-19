/*
    SPDX-FileCopyrightText: 2020 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "vsyncmonitor.h"

#include <epoxy/glx.h>
#include <GL/glxext.h>
#include "fixx11h.h"

#include <QThread>

namespace KWin
{

/**
 * The OMLSyncControlVsyncMonitorHelper class is responsible for waiting vsync events on the
 * root window. Note that the helper runs on a separate thread.
 */
class OMLSyncControlVsyncMonitorHelper : public QObject
{
    Q_OBJECT

public:
    explicit OMLSyncControlVsyncMonitorHelper(QObject *parent = nullptr);
    ~OMLSyncControlVsyncMonitorHelper() override;

    bool isValid() const;

public Q_SLOTS:
    void poll();

Q_SIGNALS:
    void errorOccurred();
    void vblankOccurred(std::chrono::nanoseconds timestamp);

private:
    Display *m_display = nullptr;
    GLXContext m_localContext = 0;
    GLXDrawable m_drawable = 0;
};

/**
 * The OMLSyncControlVsyncMonitor class monitors vblank events using the GLX_OML_sync_control
 * extension.
 *
 * Vblank events are monitored in a separated thread to avoid blocking the main thread. In
 * order to avoid locking up the main X11 connection, the worker thread establishes its own
 * X11 connection.
 */
class OMLSyncControlVsyncMonitor : public VsyncMonitor
{
    Q_OBJECT

public:
    static OMLSyncControlVsyncMonitor *create(QObject *parent);
    ~OMLSyncControlVsyncMonitor() override;

    bool isValid() const;

public Q_SLOTS:
    void arm() override;

private:
    explicit OMLSyncControlVsyncMonitor(QObject *parent = nullptr);

    QThread *m_thread = nullptr;
    OMLSyncControlVsyncMonitorHelper *m_helper = nullptr;
};

} // namespace KWin
