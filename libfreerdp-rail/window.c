/**
 * FreeRDP: A Remote Desktop Protocol Client
 * RAIL Windows
 *
 * Copyright 2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <freerdp/utils/stream.h>
#include <freerdp/utils/memory.h>
#include <freerdp/utils/hexdump.h>
#include <freerdp/utils/unicode.h>

#include <freerdp/rail/window.h>

void window_state_update(rdpWindow* window, WINDOW_ORDER_INFO* orderInfo, WINDOW_STATE_ORDER* window_state)
{
	window->fieldFlags = orderInfo->fieldFlags;

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_OWNER)
	{
		window->ownerWindowId = window_state->ownerWindowId;
		printf("ownerWindowId:0x%08X\n", window->ownerWindowId);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_STYLE)
	{
		window->style = window_state->style;
		window->extendedStyle = window_state->extendedStyle;
		printf("Style:%d, ExtendedStyle:%d\n", window->style, window->extendedStyle);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_SHOW)
	{
		window->showState = window_state->showState;
		printf("ShowState:%d\n", window->showState);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_TITLE)
	{
		window->titleInfo.length = window_state->titleInfo.length;
		window->titleInfo.string = xmalloc(window_state->titleInfo.length);
		memcpy(window->titleInfo.string, window_state->titleInfo.string, window->titleInfo.length);
		freerdp_hexdump(window->titleInfo.string, window->titleInfo.length);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_CLIENT_AREA_OFFSET)
	{
		window->clientOffsetX = window_state->clientOffsetX;
		window->clientOffsetY = window_state->clientOffsetY;

		printf("Client Area Offset: (%d, %d)\n",
				window->clientOffsetX, window->clientOffsetY);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_CLIENT_AREA_SIZE)
	{
		window->clientAreaWidth = window_state->clientAreaWidth;
		window->clientAreaHeight = window_state->clientAreaHeight;

		printf("Client Area Size: (%d, %d)\n",
				window->clientAreaWidth, window->clientAreaHeight);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_RP_CONTENT)
	{
		window->RPContent = window_state->RPContent;
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_ROOT_PARENT)
	{
		window->rootParentHandle = window_state->rootParentHandle;
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_WND_OFFSET)
	{
		window->windowOffsetX = window_state->windowOffsetX;
		window->windowOffsetY = window_state->windowOffsetY;

		printf("Window Offset: (%d, %d)\n",
				window->windowOffsetX, window->windowOffsetY);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_WND_CLIENT_DELTA)
	{
		window->windowClientDeltaX = window_state->windowClientDeltaX;
		window->windowClientDeltaY = window_state->windowClientDeltaY;

		printf("Window Client Delta: (%d, %d)\n",
				window->windowClientDeltaX, window->windowClientDeltaY);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_WND_SIZE)
	{
		window->windowWidth = window_state->windowWidth;
		window->windowHeight = window_state->windowHeight;

		printf("Window Size: (%d, %d)\n",
				window->windowWidth, window->windowHeight);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_WND_RECTS)
	{
		int i;

		for (i = 0; i < window_state->numWindowRects; i++)
		{
			printf("Window Rect #%d: left:%d top:%d right:%d bottom:%d\n", i,
					window_state->windowRects->left, window_state->windowRects->top,
					window_state->windowRects->right, window_state->windowRects->bottom);
		}
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_VIS_OFFSET)
	{
		window->visibleOffsetX = window_state->visibleOffsetX;
		window->visibleOffsetY = window_state->visibleOffsetY;

		printf("Window Visible Offset: (%d, %d)\n",
				window->visibleOffsetX, window->visibleOffsetY);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_VISIBILITY)
	{
		int i;

		for (i = 0; i < window_state->numVisibilityRects; i++)
		{
			printf("Visibility Rect #%d: left:%d top:%d right:%d bottom:%d\n", i,
					window_state->visibilityRects->left, window_state->visibilityRects->top,
					window_state->visibilityRects->right, window_state->visibilityRects->bottom);
		}
	}
}

void rail_CreateWindow(rdpRail* rail, rdpWindow* window)
{
	if (window->titleInfo.length > 0)
	{
		window->title = freerdp_uniconv_in(rail->uniconv, window->titleInfo.string, window->titleInfo.length);
	}
	else
	{
		window->title = (char*) xmalloc(sizeof("RAIL"));
		memcpy(window->title, "RAIL", sizeof("RAIL"));
	}

	IFCALL(rail->CreateWindow, rail, window);
}

void rail_UpdateWindow(rdpRail* rail, rdpWindow* window)
{
	if (window->fieldFlags & WINDOW_ORDER_FIELD_OWNER)
	{

	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_STYLE)
	{

	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_SHOW)
	{
		IFCALL(rail->ShowWindow, rail, window, window->showState);
	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_TITLE)
	{
		if (window->title != NULL)
			xfree(window->title);

		window->title = freerdp_uniconv_in(rail->uniconv, window->titleInfo.string, window->titleInfo.length);

		IFCALL(rail->SetWindowText, rail, window);
	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_CLIENT_AREA_OFFSET)
	{

	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_CLIENT_AREA_SIZE)
	{

	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_RP_CONTENT)
	{

	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_ROOT_PARENT)
	{

	}

	if ((window->fieldFlags & WINDOW_ORDER_FIELD_WND_OFFSET) ||
			(window->fieldFlags & WINDOW_ORDER_FIELD_WND_SIZE))
	{
		IFCALL(rail->MoveWindow, rail, window);
	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_WND_CLIENT_DELTA)
	{

	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_WND_RECTS)
	{

	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_VIS_OFFSET)
	{

	}

	if (window->fieldFlags & WINDOW_ORDER_FIELD_VISIBILITY)
	{

	}
}

void rail_DestroyWindow(rdpRail* rail, rdpWindow* window)
{
	IFCALL(rail->DestroyWindow, rail, window);

	if (window != NULL)
	{
		xfree(window);
	}
}