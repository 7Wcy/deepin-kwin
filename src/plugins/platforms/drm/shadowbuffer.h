/*
    KWin - the KDE window manager
    This file is part of the KDE project.

    SPDX-FileCopyrightText: 2021 Xaver Hugl <xaver.hugl@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QSize>
#include <kwinglutils.h>

namespace KWin
{

class DrmOutput;

class ShadowBuffer
{
public:
    ShadowBuffer(const QSize &size);
    ~ShadowBuffer();

    bool isComplete() const;

    void bind();
    void render(DrmOutput *output);

    int texture() const;

private:
    GLuint m_texture;
    GLuint m_framebuffer;
    QScopedPointer<GLVertexBuffer> m_vbo;
};

}