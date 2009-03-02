#include "ui_local.h"

uiQuad_t uiQuadArray[MAX_QUADS];


uiQuad_t *UI_AllocQuad()
{
	int i;
	for (i=0; i<MAX_QUADS; i++)
	{
		if (!uiQuadArray[i].inUse)
		{
			uiQuadArray[i].inUse = qtrue;
			return &uiQuadArray[i];
		}
	}
	return NULL;
}

uiQuad_t* QuadList_Add(uiQuadList_t *list, float x, float y, float w, float h, const float *u, const float *v, const float *color, float s, float t, float s2, float t2,
		    qhandle_t hShader)
{
	if (list)
	{
		uiQuad_t *quad = UI_AllocQuad();
		if (quad)
		{
			quad->next = NULL;
			if (!list->qList)
			{
				list->qList = quad;
			} else {
				uiQuad_t *p=list->qList;
				while (p && p->next)
				{
					p = p->next;
				}
				p->next=quad;
			}
			if (color)
			{
				quad->verts[0].modulate[0] = quad->verts[1].modulate[0] = quad->verts[2].modulate[0] = quad->verts[3].modulate[0] = ((int)(color[0]*255))&255;
				quad->verts[0].modulate[1] = quad->verts[1].modulate[1] = quad->verts[2].modulate[1] = quad->verts[3].modulate[1] = ((int)(color[1]*255))&255;
				quad->verts[0].modulate[2] = quad->verts[1].modulate[2] = quad->verts[2].modulate[2] = quad->verts[3].modulate[2] = ((int)(color[2]*255))&255;
				quad->verts[0].modulate[3] = quad->verts[1].modulate[3] = quad->verts[2].modulate[3] = quad->verts[3].modulate[3] = ((int)(color[3]*255))&255;
				quad->keepColor = qtrue;
			} else {
				quad->verts[0].modulate[0] = quad->verts[1].modulate[0] = quad->verts[2].modulate[0] = quad->verts[3].modulate[0] = 255;
				quad->verts[0].modulate[1] = quad->verts[1].modulate[1] = quad->verts[2].modulate[1] = quad->verts[3].modulate[1] = 255;
				quad->verts[0].modulate[2] = quad->verts[1].modulate[2] = quad->verts[2].modulate[2] = quad->verts[3].modulate[2] = 255;
				quad->verts[0].modulate[3] = quad->verts[1].modulate[3] = quad->verts[2].modulate[3] = quad->verts[3].modulate[3] = 255;
				quad->keepColor = qfalse;
			}
			quad->verts[0].st[0]=s;
			quad->verts[0].st[1]=t;
			quad->verts[1].st[0]=s2;
			quad->verts[1].st[1]=t;
			quad->verts[2].st[0]=s2;
			quad->verts[2].st[1]=t2;
			quad->verts[3].st[0]=s;
			quad->verts[3].st[1]=t2;
			VectorSet(quad->verts[0].xyz, 320, 320-x, 240-y);
			VectorSet(quad->verts[1].xyz, 320, quad->verts[0].xyz[1]-u[0]*w, quad->verts[0].xyz[2]-u[1]*w);
			VectorSet(quad->verts[2].xyz, 320, quad->verts[1].xyz[1]-v[0]*h, quad->verts[1].xyz[2]-v[1]*h);
			VectorSet(quad->verts[3].xyz, 320, quad->verts[0].xyz[1]-v[0]*h, quad->verts[0].xyz[2]-v[1]*h);
			//uiInfo.uiDC.polyZ += UI_POLY_Z_OFFSET;
			quad->hShader = hShader;
			return quad;
		}
	}
	return NULL;
}

void QuadList_SetCursorColor(uiQuadList_t *list, const float *color)
{
	if (!list || !list->qCursor)
		return;
	if (color)
	{
		unsigned char r, g, b, a;
		int clr;
		r = color[0] * 255;
		g = color[1] * 255;
		b = color[2] * 255;
		a = color[3] * 255;
		_asm {
			mov bl, b;
			mov bh, a;
			shl ebx, 16;
			mov bl, r;
			mov bh, g;
			mov clr, ebx;
			mov eax, list;
			mov eax, [eax+4];	//list->qCursor
			mov dword ptr[eax+20], ebx;		//list->qCursor->verts[0].modulate
			mov dword ptr[eax+44], ebx;		//list->qCursor->verts[1].modulate
			mov dword ptr[eax+68], ebx;		//list->qCursor->verts[2].modulate
			mov dword ptr[eax+92], ebx;		//list->qCursor->verts[3].modulate
		}
	}
	list->qCursor = list->qCursor->next;
}

void QuadList_Print(uiQuadList_t *quadList, const float *color)
{
	if (quadList && quadList->qList)
	{
		unsigned char r, g, b, a;
		int clr;
		uiQuad_t *p = quadList->qList;
		/*
		refdef_t scene;
		
		memset(&scene, 0, sizeof(scene));
		scene.x=0;
		scene.y=0;
		scene.width=640 * uiInfo.uiDC.xscale;
		scene.height=480 * uiInfo.uiDC.yscale ;
		scene.fov_x=90;
		scene.fov_y=73.739795291688042593711225118187f;
		scene.rdflags = RDF_NOWORLDMODEL;
		AxisClear(scene.viewaxis);
		trap_R_ClearScene();
		*/
		
		if (color)
		{
			r = color[0] * 255;
			g = color[1] * 255;
			b = color[2] * 255;
			a = color[3] * 255;
			_asm {
				mov al, b;
				mov ah, a;
				shl eax, 16;
				mov al, r;
				mov ah, g;
				mov clr, eax;
			}
		}
		while (p)
		{
			if (color && !p->keepColor)
			{
				_asm {
					mov ebx, clr;
					mov eax, p;
					mov dword ptr[eax+20], ebx;		//p->verts[0].modulate
					mov dword ptr[eax+44], ebx;		//p->verts[1].modulate
					mov dword ptr[eax+68], ebx;		//p->verts[2].modulate
					mov dword ptr[eax+92], ebx;		//p->verts[3].modulate
				}
			}
			//trap_R_AddPolyToScene(p->hShader, 4, p->verts);
			//uiInfo.uiDC.pendingPolys++;

			UI_AddQuadToScene(p->hShader, p->verts);

			p = p->next;
		}
		//trap_R_RenderScene(&uiInfo.uiDC.scene2D);
	}
}

void QuadList_Clear(uiQuadList_t *list)
{
	if (list)
	{
		uiQuad_t *p = list->qList;
		while (p)
		{
			p->inUse = qfalse;
			p = p->next;
		}
	}
	list->qList = NULL;
}


//-----------------------------------------------

//
// ui_polyalloc.c
//

typedef struct uiQuad_s
{
	polyVert_t verts[4];
	qhandle_t hShader;
	qboolean inUse, keepColor;
	struct uiQuad_s *next;	
} uiQuad_t;

#define MAX_QUADS	2048
extern uiQuad_t uiQuadArray[MAX_QUADS];

typedef struct
{
	uiQuad_t *qList, *qCursor;
} uiQuadList_t;

