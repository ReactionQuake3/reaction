export Com_Clamp
code
proc Com_Clamp 0 0
file "../../game/q_shared.c"
line 23
;1://-----------------------------------------------------------------------------
;2://
;3:// $Id$
;4://
;5://-----------------------------------------------------------------------------
;6://
;7:// $Log$
;7:// Revision 1.1  2002/01/08 05:46:24  blaze
;7:// Initial revision
;7://
;8:// Revision 1.4  2001/12/31 16:28:42  jbravo
;9:// I made a Booboo with the Log tag.
;10://
;11://
;12://-----------------------------------------------------------------------------
;13:// Copyright (C) 1999-2000 Id Software, Inc.
;14:
;15://
;16:
;17:// q_shared.c -- stateless support routines that are included in each code dll
;18:
;19:#include "q_shared.h"
;20:
;21:
;22:
;23:float Com_Clamp( float min, float max, float value ) {
line 25
;24:
;25:	if ( value < min ) {
ADDRFP4 8
INDIRF4
ADDRFP4 0
INDIRF4
GEF4 $23
line 27
;26:
;27:		return min;
ADDRFP4 0
INDIRF4
RETF4
ADDRGP4 $22
JUMPV
LABELV $23
line 31
;28:
;29:	}
;30:
;31:	if ( value > max ) {
ADDRFP4 8
INDIRF4
ADDRFP4 4
INDIRF4
LEF4 $25
line 33
;32:
;33:		return max;
ADDRFP4 4
INDIRF4
RETF4
ADDRGP4 $22
JUMPV
LABELV $25
line 37
;34:
;35:	}
;36:
;37:	return value;
ADDRFP4 8
INDIRF4
RETF4
LABELV $22
endproc Com_Clamp 0 0
export COM_SkipPath
proc COM_SkipPath 4 0
line 57
;38:
;39:}
;40:
;41:
;42:
;43:
;44:
;45:/*
;46:
;47:============
;48:
;49:COM_SkipPath
;50:
;51:============
;52:
;53:*/
;54:
;55:char *COM_SkipPath (char *pathname)
;56:
;57:{
line 63
;58:
;59:	char	*last;
;60:
;61:	
;62:
;63:	last = pathname;
ADDRLP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRGP4 $29
JUMPV
LABELV $28
line 67
;64:
;65:	while (*pathname)
;66:
;67:	{
line 69
;68:
;69:		if (*pathname=='/')
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 47
NEI4 $31
line 71
;70:
;71:			last = pathname+1;
ADDRLP4 0
ADDRFP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
LABELV $31
line 73
;72:
;73:		pathname++;
ADDRFP4 0
ADDRFP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 75
;74:
;75:	}
LABELV $29
line 65
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $28
line 77
;76:
;77:	return last;
ADDRLP4 0
INDIRP4
RETP4
LABELV $27
endproc COM_SkipPath 4 0
export COM_StripExtension
proc COM_StripExtension 12 0
line 93
;78:
;79:}
;80:
;81:
;82:
;83:/*
;84:
;85:============
;86:
;87:COM_StripExtension
;88:
;89:============
;90:
;91:*/
;92:
;93:void COM_StripExtension( const char *in, char *out ) {
ADDRGP4 $35
JUMPV
LABELV $34
line 95
;94:
;95:	while ( *in && *in != '.' ) {
line 97
;96:
;97:		*out++ = *in++;
ADDRLP4 0
ADDRFP4 4
INDIRP4
ASGNP4
ADDRLP4 8
CNSTI4 1
ASGNI4
ADDRFP4 4
ADDRLP4 0
INDIRP4
ADDRLP4 8
INDIRI4
ADDP4
ASGNP4
ADDRLP4 4
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
ADDRLP4 4
INDIRP4
ADDRLP4 8
INDIRI4
ADDP4
ASGNP4
ADDRLP4 0
INDIRP4
ADDRLP4 4
INDIRP4
INDIRI1
ASGNI1
line 99
;98:
;99:	}
LABELV $35
line 95
ADDRLP4 0
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 0
INDIRI4
CNSTI4 0
EQI4 $37
ADDRLP4 0
INDIRI4
CNSTI4 46
NEI4 $34
LABELV $37
line 101
;100:
;101:	*out = 0;
ADDRFP4 4
INDIRP4
CNSTI1 0
ASGNI1
line 103
;102:
;103:}
LABELV $33
endproc COM_StripExtension 12 0
export COM_DefaultExtension
proc COM_DefaultExtension 76 20
line 119
;104:
;105:
;106:
;107:
;108:
;109:/*
;110:
;111:==================
;112:
;113:COM_DefaultExtension
;114:
;115:==================
;116:
;117:*/
;118:
;119:void COM_DefaultExtension (char *path, int maxSize, const char *extension ) {
line 135
;120:
;121:	char	oldPath[MAX_QPATH];
;122:
;123:	char    *src;
;124:
;125:
;126:
;127://
;128:
;129:// if path doesn't have a .EXT, append extension
;130:
;131:// (extension should include the .)
;132:
;133://
;134:
;135:	src = path + strlen(path) - 1;
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 68
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 0
ADDRLP4 68
INDIRI4
ADDRFP4 0
INDIRP4
ADDP4
CNSTI4 -1
ADDP4
ASGNP4
ADDRGP4 $40
JUMPV
LABELV $39
line 139
;136:
;137:
;138:
;139:	while (*src != '/' && src != path) {
line 141
;140:
;141:		if ( *src == '.' ) {
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 46
NEI4 $42
line 143
;142:
;143:			return;                 // it has an extension
ADDRGP4 $38
JUMPV
LABELV $42
line 147
;144:
;145:		}
;146:
;147:		src--;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 -1
ADDP4
ASGNP4
line 149
;148:
;149:	}
LABELV $40
line 139
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 47
EQI4 $44
ADDRLP4 0
INDIRP4
CVPU4 4
ADDRFP4 0
INDIRP4
CVPU4 4
NEU4 $39
LABELV $44
line 153
;150:
;151:
;152:
;153:	Q_strncpyz( oldPath, path, sizeof( oldPath ) );
ADDRLP4 4
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
CNSTI4 64
ARGI4
ADDRGP4 Q_strncpyz
CALLV
pop
line 155
;154:
;155:	Com_sprintf( path, maxSize, "%s%s", oldPath, extension );
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 4
INDIRI4
ARGI4
ADDRGP4 $45
ARGP4
ADDRLP4 4
ARGP4
ADDRFP4 8
INDIRP4
ARGP4
ADDRGP4 Com_sprintf
CALLV
pop
line 157
;156:
;157:}
LABELV $38
endproc COM_DefaultExtension 76 20
export ShortSwap
proc ShortSwap 2 0
ADDRFP4 0
ADDRFP4 0
INDIRI4
CVII2 4
ASGNI2
line 221
;158:
;159:
;160:
;161:/*
;162:
;163:============================================================================
;164:
;165:
;166:
;167:					BYTE ORDER FUNCTIONS
;168:
;169:
;170:
;171:============================================================================
;172:
;173:*/
;174:
;175:/*
;176:
;177:// can't just use function pointers, or dll linkage can
;178:
;179:// mess up when qcommon is included in multiple places
;180:
;181:static short	(*_BigShort) (short l);
;182:
;183:static short	(*_LittleShort) (short l);
;184:
;185:static int		(*_BigLong) (int l);
;186:
;187:static int		(*_LittleLong) (int l);
;188:
;189:static qint64	(*_BigLong64) (qint64 l);
;190:
;191:static qint64	(*_LittleLong64) (qint64 l);
;192:
;193:static float	(*_BigFloat) (const float *l);
;194:
;195:static float	(*_LittleFloat) (const float *l);
;196:
;197:
;198:
;199:short	BigShort(short l){return _BigShort(l);}
;200:
;201:short	LittleShort(short l) {return _LittleShort(l);}
;202:
;203:int		BigLong (int l) {return _BigLong(l);}
;204:
;205:int		LittleLong (int l) {return _LittleLong(l);}
;206:
;207:qint64 	BigLong64 (qint64 l) {return _BigLong64(l);}
;208:
;209:qint64 	LittleLong64 (qint64 l) {return _LittleLong64(l);}
;210:
;211:float	BigFloat (const float *l) {return _BigFloat(l);}
;212:
;213:float	LittleFloat (const float *l) {return _LittleFloat(l);}
;214:
;215:*/
;216:
;217:
;218:
;219:short   ShortSwap (short l)
;220:
;221:{
line 227
;222:
;223:	byte    b1,b2;
;224:
;225:
;226:
;227:	b1 = l&255;
ADDRLP4 0
ADDRFP4 0
INDIRI2
CVII4 2
CNSTI4 255
BANDI4
CVIU4 4
CVUU1 4
ASGNU1
line 229
;228:
;229:	b2 = (l>>8)&255;
ADDRLP4 1
ADDRFP4 0
INDIRI2
CVII4 2
CNSTI4 8
RSHI4
CNSTI4 255
BANDI4
CVIU4 4
CVUU1 4
ASGNU1
line 233
;230:
;231:
;232:
;233:	return (b1<<8) + b2;
ADDRLP4 0
INDIRU1
CVUI4 1
CNSTI4 8
LSHI4
ADDRLP4 1
INDIRU1
CVUI4 1
ADDI4
CVII2 4
CVII4 2
RETI4
LABELV $46
endproc ShortSwap 2 0
export ShortNoSwap
proc ShortNoSwap 0 0
ADDRFP4 0
ADDRFP4 0
INDIRI4
CVII2 4
ASGNI2
line 241
;234:
;235:}
;236:
;237:
;238:
;239:short	ShortNoSwap (short l)
;240:
;241:{
line 243
;242:
;243:	return l;
ADDRFP4 0
INDIRI2
CVII4 2
RETI4
LABELV $47
endproc ShortNoSwap 0 0
export LongSwap
proc LongSwap 4 0
line 251
;244:
;245:}
;246:
;247:
;248:
;249:int    LongSwap (int l)
;250:
;251:{
line 257
;252:
;253:	byte    b1,b2,b3,b4;
;254:
;255:
;256:
;257:	b1 = l&255;
ADDRLP4 0
ADDRFP4 0
INDIRI4
CNSTI4 255
BANDI4
CVIU4 4
CVUU1 4
ASGNU1
line 259
;258:
;259:	b2 = (l>>8)&255;
ADDRLP4 1
ADDRFP4 0
INDIRI4
CNSTI4 8
RSHI4
CNSTI4 255
BANDI4
CVIU4 4
CVUU1 4
ASGNU1
line 261
;260:
;261:	b3 = (l>>16)&255;
ADDRLP4 2
ADDRFP4 0
INDIRI4
CNSTI4 16
RSHI4
CNSTI4 255
BANDI4
CVIU4 4
CVUU1 4
ASGNU1
line 263
;262:
;263:	b4 = (l>>24)&255;
ADDRLP4 3
ADDRFP4 0
INDIRI4
CNSTI4 24
RSHI4
CNSTI4 255
BANDI4
CVIU4 4
CVUU1 4
ASGNU1
line 267
;264:
;265:
;266:
;267:	return ((int)b1<<24) + ((int)b2<<16) + ((int)b3<<8) + b4;
ADDRLP4 0
INDIRU1
CVUI4 1
CNSTI4 24
LSHI4
ADDRLP4 1
INDIRU1
CVUI4 1
CNSTI4 16
LSHI4
ADDI4
ADDRLP4 2
INDIRU1
CVUI4 1
CNSTI4 8
LSHI4
ADDI4
ADDRLP4 3
INDIRU1
CVUI4 1
ADDI4
RETI4
LABELV $48
endproc LongSwap 4 0
export LongNoSwap
proc LongNoSwap 0 0
line 275
;268:
;269:}
;270:
;271:
;272:
;273:int	LongNoSwap (int l)
;274:
;275:{
line 277
;276:
;277:	return l;
ADDRFP4 0
INDIRI4
RETI4
LABELV $49
endproc LongNoSwap 0 0
export Long64Swap
proc Long64Swap 8 0
line 285
;278:
;279:}
;280:
;281:
;282:
;283:qint64 Long64Swap (qint64 ll)
;284:
;285:{
line 291
;286:
;287:	qint64	result;
;288:
;289:
;290:
;291:	result.b0 = ll.b7;
ADDRLP4 0
ADDRFP4 4
INDIRP4
CNSTI4 7
ADDP4
INDIRU1
ASGNU1
line 293
;292:
;293:	result.b1 = ll.b6;
ADDRLP4 0+1
ADDRFP4 4
INDIRP4
CNSTI4 6
ADDP4
INDIRU1
ASGNU1
line 295
;294:
;295:	result.b2 = ll.b5;
ADDRLP4 0+2
ADDRFP4 4
INDIRP4
CNSTI4 5
ADDP4
INDIRU1
ASGNU1
line 297
;296:
;297:	result.b3 = ll.b4;
ADDRLP4 0+3
ADDRFP4 4
INDIRP4
CNSTI4 4
ADDP4
INDIRU1
ASGNU1
line 299
;298:
;299:	result.b4 = ll.b3;
ADDRLP4 0+4
ADDRFP4 4
INDIRP4
CNSTI4 3
ADDP4
INDIRU1
ASGNU1
line 301
;300:
;301:	result.b5 = ll.b2;
ADDRLP4 0+5
ADDRFP4 4
INDIRP4
CNSTI4 2
ADDP4
INDIRU1
ASGNU1
line 303
;302:
;303:	result.b6 = ll.b1;
ADDRLP4 0+6
ADDRFP4 4
INDIRP4
CNSTI4 1
ADDP4
INDIRU1
ASGNU1
line 305
;304:
;305:	result.b7 = ll.b0;
ADDRLP4 0+7
ADDRFP4 4
INDIRP4
INDIRU1
ASGNU1
line 309
;306:
;307:
;308:
;309:	return result;
ADDRFP4 0
INDIRP4
ADDRLP4 0
INDIRB
ASGNB 8
LABELV $50
endproc Long64Swap 8 0
export Long64NoSwap
proc Long64NoSwap 0 0
line 317
;310:
;311:}
;312:
;313:
;314:
;315:qint64 Long64NoSwap (qint64 ll)
;316:
;317:{
line 319
;318:
;319:	return ll;
ADDRFP4 0
INDIRP4
ADDRFP4 4
INDIRP4
INDIRB
ASGNB 8
LABELV $59
endproc Long64NoSwap 0 0
export FloatSwap
proc FloatSwap 12 4
line 335
;320:
;321:}
;322:
;323:
;324:
;325:typedef union {
;326:
;327:		float	f;
;328:
;329:    unsigned int i;
;330:
;331:} _FloatByteUnion;
;332:
;333:	
;334:
;335:float FloatSwap (const float *f) {
line 343
;336:
;337:	const _FloatByteUnion *in;
;338:
;339:	_FloatByteUnion out;
;340:
;341:	
;342:
;343:	in = (_FloatByteUnion *)f;
ADDRLP4 0
ADDRFP4 0
INDIRP4
ASGNP4
line 345
;344:
;345:	out.i = LongSwap(in->i);
ADDRLP4 0
INDIRP4
INDIRU4
CVUI4 4
ARGI4
ADDRLP4 8
ADDRGP4 LongSwap
CALLI4
ASGNI4
ADDRLP4 4
ADDRLP4 8
INDIRI4
CVIU4 4
ASGNU4
line 349
;346:
;347:
;348:
;349:	return out.f;
ADDRLP4 4
INDIRF4
RETF4
LABELV $62
endproc FloatSwap 12 4
export FloatNoSwap
proc FloatNoSwap 0 0
line 357
;350:
;351:}
;352:
;353:
;354:
;355:float FloatNoSwap (const float *f)
;356:
;357:{
line 359
;358:
;359:	return *f;
ADDRFP4 0
INDIRP4
INDIRF4
RETF4
LABELV $63
endproc FloatNoSwap 0 0
export COM_BeginParseSession
proc COM_BeginParseSession 0 16
line 465
;360:
;361:}
;362:
;363:
;364:
;365:/*
;366:
;367:================
;368:
;369:Swap_Init
;370:
;371:================
;372:
;373:*/
;374:
;375:/*
;376:
;377:void Swap_Init (void)
;378:
;379:{
;380:
;381:	byte	swaptest[2] = {1,0};
;382:
;383:
;384:
;385:// set the byte swapping variables in a portable manner	
;386:
;387:	if ( *(short *)swaptest == 1)
;388:
;389:	{
;390:
;391:		_BigShort = ShortSwap;
;392:
;393:		_LittleShort = ShortNoSwap;
;394:
;395:		_BigLong = LongSwap;
;396:
;397:		_LittleLong = LongNoSwap;
;398:
;399:		_BigLong64 = Long64Swap;
;400:
;401:		_LittleLong64 = Long64NoSwap;
;402:
;403:		_BigFloat = FloatSwap;
;404:
;405:		_LittleFloat = FloatNoSwap;
;406:
;407:	}
;408:
;409:	else
;410:
;411:	{
;412:
;413:		_BigShort = ShortNoSwap;
;414:
;415:		_LittleShort = ShortSwap;
;416:
;417:		_BigLong = LongNoSwap;
;418:
;419:		_LittleLong = LongSwap;
;420:
;421:		_BigLong64 = Long64NoSwap;
;422:
;423:		_LittleLong64 = Long64Swap;
;424:
;425:		_BigFloat = FloatNoSwap;
;426:
;427:		_LittleFloat = FloatSwap;
;428:
;429:	}
;430:
;431:
;432:
;433:}
;434:
;435:*/
;436:
;437:
;438:
;439:/*
;440:
;441:============================================================================
;442:
;443:
;444:
;445:PARSING
;446:
;447:
;448:
;449:============================================================================
;450:
;451:*/
;452:
;453:
;454:
;455:static	char	com_token[MAX_TOKEN_CHARS];
;456:
;457:static	char	com_parsename[MAX_TOKEN_CHARS];
;458:
;459:static	int		com_lines;
;460:
;461:
;462:
;463:void COM_BeginParseSession( const char *name )
;464:
;465:{
line 467
;466:
;467:	com_lines = 0;
ADDRGP4 com_lines
CNSTI4 0
ASGNI4
line 469
;468:
;469:	Com_sprintf(com_parsename, sizeof(com_parsename), "%s", name);
ADDRGP4 com_parsename
ARGP4
CNSTI4 1024
ARGI4
ADDRGP4 $65
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 Com_sprintf
CALLV
pop
line 471
;470:
;471:}
LABELV $64
endproc COM_BeginParseSession 0 16
export COM_GetCurrentParseLine
proc COM_GetCurrentParseLine 0 0
line 477
;472:
;473:
;474:
;475:int COM_GetCurrentParseLine( void )
;476:
;477:{
line 479
;478:
;479:	return com_lines;
ADDRGP4 com_lines
INDIRI4
RETI4
LABELV $66
endproc COM_GetCurrentParseLine 0 0
export COM_Parse
proc COM_Parse 4 8
line 487
;480:
;481:}
;482:
;483:
;484:
;485:char *COM_Parse( char **data_p )
;486:
;487:{
line 489
;488:
;489:	return COM_ParseExt( data_p, qtrue );
ADDRFP4 0
INDIRP4
ARGP4
CNSTI4 1
ARGI4
ADDRLP4 0
ADDRGP4 COM_ParseExt
CALLP4
ASGNP4
ADDRLP4 0
INDIRP4
RETP4
LABELV $67
endproc COM_Parse 4 8
bss
align 1
LABELV $69
skip 4096
export COM_ParseError
code
proc COM_ParseError 4 16
line 497
;490:
;491:}
;492:
;493:
;494:
;495:void COM_ParseError( char *format, ... )
;496:
;497:{
line 505
;498:
;499:	va_list argptr;
;500:
;501:	static char string[4096];
;502:
;503:
;504:
;505:	va_start (argptr, format);
ADDRLP4 0
ADDRFP4 0+4
ASGNP4
line 507
;506:
;507:	vsprintf (string, format, argptr);
ADDRGP4 $69
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 vsprintf
CALLI4
pop
line 509
;508:
;509:	va_end (argptr);
ADDRLP4 0
CNSTP4 0
ASGNP4
line 513
;510:
;511:
;512:
;513:	Com_Printf("ERROR: %s, line %d: %s\n", com_parsename, com_lines, string);
ADDRGP4 $71
ARGP4
ADDRGP4 com_parsename
ARGP4
ADDRGP4 com_lines
INDIRI4
ARGI4
ADDRGP4 $69
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
line 515
;514:
;515:}
LABELV $68
endproc COM_ParseError 4 16
bss
align 1
LABELV $73
skip 4096
export COM_ParseWarning
code
proc COM_ParseWarning 4 16
line 521
;516:
;517:
;518:
;519:void COM_ParseWarning( char *format, ... )
;520:
;521:{
line 529
;522:
;523:	va_list argptr;
;524:
;525:	static char string[4096];
;526:
;527:
;528:
;529:	va_start (argptr, format);
ADDRLP4 0
ADDRFP4 0+4
ASGNP4
line 531
;530:
;531:	vsprintf (string, format, argptr);
ADDRGP4 $73
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 vsprintf
CALLI4
pop
line 533
;532:
;533:	va_end (argptr);
ADDRLP4 0
CNSTP4 0
ASGNP4
line 537
;534:
;535:
;536:
;537:	Com_Printf("WARNING: %s, line %d: %s\n", com_parsename, com_lines, string);
ADDRGP4 $75
ARGP4
ADDRGP4 com_parsename
ARGP4
ADDRGP4 com_lines
INDIRI4
ARGI4
ADDRGP4 $73
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
line 539
;538:
;539:}
LABELV $72
endproc COM_ParseWarning 4 16
proc SkipWhitespace 8 0
line 567
;540:
;541:
;542:
;543:/*
;544:
;545:==============
;546:
;547:COM_Parse
;548:
;549:
;550:
;551:Parse a token out of a string
;552:
;553:Will never return NULL, just empty strings
;554:
;555:
;556:
;557:If "allowLineBreaks" is qtrue then an empty
;558:
;559:string will be returned if the next token is
;560:
;561:a newline.
;562:
;563:==============
;564:
;565:*/
;566:
;567:static char *SkipWhitespace( char *data, qboolean *hasNewLines ) {
ADDRGP4 $78
JUMPV
LABELV $77
line 573
;568:
;569:	int c;
;570:
;571:
;572:
;573:	while( (c = *data) <= ' ') {
line 575
;574:
;575:		if( !c ) {
ADDRLP4 0
INDIRI4
CNSTI4 0
NEI4 $80
line 577
;576:
;577:			return NULL;
CNSTP4 0
RETP4
ADDRGP4 $76
JUMPV
LABELV $80
line 581
;578:
;579:		}
;580:
;581:		if( c == '\n' ) {
ADDRLP4 0
INDIRI4
CNSTI4 10
NEI4 $82
line 583
;582:
;583:			com_lines++;
ADDRLP4 4
ADDRGP4 com_lines
ASGNP4
ADDRLP4 4
INDIRP4
ADDRLP4 4
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
line 585
;584:
;585:			*hasNewLines = qtrue;
ADDRFP4 4
INDIRP4
CNSTI4 1
ASGNI4
line 587
;586:
;587:		}
LABELV $82
line 589
;588:
;589:		data++;
ADDRFP4 0
ADDRFP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 591
;590:
;591:	}
LABELV $78
line 573
ADDRLP4 4
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 0
ADDRLP4 4
INDIRI4
ASGNI4
ADDRLP4 4
INDIRI4
CNSTI4 32
LEI4 $77
line 595
;592:
;593:
;594:
;595:	return data;
ADDRFP4 0
INDIRP4
RETP4
LABELV $76
endproc SkipWhitespace 8 0
export COM_Compress
proc COM_Compress 48 0
line 601
;596:
;597:}
;598:
;599:
;600:
;601:int COM_Compress( char *data_p ) {
line 607
;602:
;603:	char *in, *out;
;604:
;605:	int c;
;606:
;607:	qboolean newline = qfalse, whitespace = qfalse;
ADDRLP4 12
CNSTI4 0
ASGNI4
ADDRLP4 16
CNSTI4 0
ASGNI4
line 611
;608:
;609:
;610:
;611:	in = out = data_p;
ADDRLP4 20
ADDRFP4 0
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 20
INDIRP4
ASGNP4
ADDRLP4 0
ADDRLP4 20
INDIRP4
ASGNP4
line 613
;612:
;613:	if (in) {
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $85
ADDRGP4 $88
JUMPV
LABELV $87
line 615
;614:
;615:		while ((c = *in) != 0) {
line 619
;616:
;617:			// skip double slash comments
;618:
;619:			if ( c == '/' && in[1] == '/' ) {
ADDRLP4 24
CNSTI4 47
ASGNI4
ADDRLP4 4
INDIRI4
ADDRLP4 24
INDIRI4
NEI4 $90
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
INDIRI1
CVII4 1
ADDRLP4 24
INDIRI4
NEI4 $90
ADDRGP4 $93
JUMPV
LABELV $92
line 621
;620:
;621:				while (*in && *in != '\n') {
line 623
;622:
;623:					in++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 625
;624:
;625:				}
LABELV $93
line 621
ADDRLP4 28
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 28
INDIRI4
CNSTI4 0
EQI4 $95
ADDRLP4 28
INDIRI4
CNSTI4 10
NEI4 $92
LABELV $95
line 629
;626:
;627:			// skip /* */ comments
;628:
;629:			} else if ( c == '/' && in[1] == '*' ) {
ADDRGP4 $91
JUMPV
LABELV $90
ADDRLP4 4
INDIRI4
CNSTI4 47
NEI4 $96
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
INDIRI1
CVII4 1
CNSTI4 42
NEI4 $96
ADDRGP4 $99
JUMPV
LABELV $98
line 633
;630:
;631:				while ( *in && ( *in != '*' || in[1] != '/' ) ) 
;632:
;633:					in++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
LABELV $99
line 631
ADDRLP4 32
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 32
INDIRI4
CNSTI4 0
EQI4 $101
ADDRLP4 32
INDIRI4
CNSTI4 42
NEI4 $98
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
INDIRI1
CVII4 1
CNSTI4 47
NEI4 $98
LABELV $101
line 635
;634:
;635:				if ( *in ) 
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
EQI4 $97
line 637
;636:
;637:					in += 2;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 2
ADDP4
ASGNP4
line 641
;638:
;639:                        // record when we hit a newline
;640:
;641:                        } else if ( c == '\n' || c == '\r' ) {
ADDRGP4 $97
JUMPV
LABELV $96
ADDRLP4 4
INDIRI4
CNSTI4 10
EQI4 $106
ADDRLP4 4
INDIRI4
CNSTI4 13
NEI4 $104
LABELV $106
line 643
;642:
;643:                            newline = qtrue;
ADDRLP4 12
CNSTI4 1
ASGNI4
line 645
;644:
;645:                            in++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 649
;646:
;647:                        // record when we hit whitespace
;648:
;649:                        } else if ( c == ' ' || c == '\t') {
ADDRGP4 $105
JUMPV
LABELV $104
ADDRLP4 4
INDIRI4
CNSTI4 32
EQI4 $109
ADDRLP4 4
INDIRI4
CNSTI4 9
NEI4 $107
LABELV $109
line 651
;650:
;651:                            whitespace = qtrue;
ADDRLP4 16
CNSTI4 1
ASGNI4
line 653
;652:
;653:                            in++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 657
;654:
;655:                        // an actual token
;656:
;657:			} else {
ADDRGP4 $108
JUMPV
LABELV $107
line 661
;658:
;659:                            // if we have a pending newline, emit it (and it counts as whitespace)
;660:
;661:                            if (newline) {
ADDRLP4 12
INDIRI4
CNSTI4 0
EQI4 $110
line 663
;662:
;663:                                *out++ = '\n';
ADDRLP4 36
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 36
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 36
INDIRP4
CNSTI1 10
ASGNI1
line 665
;664:
;665:                                newline = qfalse;
ADDRLP4 12
CNSTI4 0
ASGNI4
line 667
;666:
;667:                                whitespace = qfalse;
ADDRLP4 16
CNSTI4 0
ASGNI4
line 669
;668:
;669:                            } if (whitespace) {
LABELV $110
ADDRLP4 16
INDIRI4
CNSTI4 0
EQI4 $112
line 671
;670:
;671:                                *out++ = ' ';
ADDRLP4 36
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 36
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 36
INDIRP4
CNSTI1 32
ASGNI1
line 673
;672:
;673:                                whitespace = qfalse;
ADDRLP4 16
CNSTI4 0
ASGNI4
line 675
;674:
;675:                            }
LABELV $112
line 681
;676:
;677:                            
;678:
;679:                            // copy quoted strings unmolested
;680:
;681:                            if (c == '"') {
ADDRLP4 4
INDIRI4
CNSTI4 34
NEI4 $114
line 683
;682:
;683:                                    *out++ = c;
ADDRLP4 36
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 36
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 36
INDIRP4
ADDRLP4 4
INDIRI4
CVII1 4
ASGNI1
line 685
;684:
;685:                                    in++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRGP4 $117
JUMPV
LABELV $116
line 687
;686:
;687:                                    while (1) {
line 689
;688:
;689:                                        c = *in;
ADDRLP4 4
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
line 691
;690:
;691:                                        if (c && c != '"') {
ADDRLP4 4
INDIRI4
CNSTI4 0
EQI4 $118
ADDRLP4 4
INDIRI4
CNSTI4 34
EQI4 $118
line 693
;692:
;693:                                            *out++ = c;
ADDRLP4 44
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 44
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 44
INDIRP4
ADDRLP4 4
INDIRI4
CVII1 4
ASGNI1
line 695
;694:
;695:                                            in++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 697
;696:
;697:                                        } else {
line 699
;698:
;699:                                            break;
LABELV $120
line 703
;700:
;701:                                        }
;702:
;703:				}
LABELV $117
line 687
ADDRGP4 $116
JUMPV
LABELV $118
line 705
;704:
;705:                                    if (c == '"') {
ADDRLP4 4
INDIRI4
CNSTI4 34
NEI4 $115
line 707
;706:
;707:                                        *out++ = c;
ADDRLP4 40
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 40
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 40
INDIRP4
ADDRLP4 4
INDIRI4
CVII1 4
ASGNI1
line 709
;708:
;709:                                        in++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 711
;710:
;711:				}
line 713
;712:
;713:			} else {
ADDRGP4 $115
JUMPV
LABELV $114
line 715
;714:
;715:                                *out = c;
ADDRLP4 8
INDIRP4
ADDRLP4 4
INDIRI4
CVII1 4
ASGNI1
line 717
;716:
;717:                                out++;
ADDRLP4 8
ADDRLP4 8
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 719
;718:
;719:                                in++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 721
;720:
;721:				}
LABELV $115
line 723
;722:
;723:			}
LABELV $108
LABELV $105
LABELV $97
LABELV $91
line 725
;724:
;725:		}
LABELV $88
line 615
ADDRLP4 24
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 4
ADDRLP4 24
INDIRI4
ASGNI4
ADDRLP4 24
INDIRI4
CNSTI4 0
NEI4 $87
line 727
;726:
;727:	}
LABELV $85
line 729
;728:
;729:	*out = 0;
ADDRLP4 8
INDIRP4
CNSTI1 0
ASGNI1
line 731
;730:
;731:	return out - data_p;
ADDRLP4 8
INDIRP4
CVPU4 4
ADDRFP4 0
INDIRP4
CVPU4 4
SUBU4
CVUI4 4
RETI4
LABELV $84
endproc COM_Compress 48 0
export COM_ParseExt
proc COM_ParseExt 36 8
line 739
;732:
;733:}
;734:
;735:
;736:
;737:char *COM_ParseExt( char **data_p, qboolean allowLineBreaks )
;738:
;739:{
line 741
;740:
;741:	int c = 0, len;
ADDRLP4 4
CNSTI4 0
ASGNI4
line 743
;742:
;743:	qboolean hasNewLines = qfalse;
ADDRLP4 12
CNSTI4 0
ASGNI4
line 749
;744:
;745:	char *data;
;746:
;747:
;748:
;749:	data = *data_p;
ADDRLP4 0
ADDRFP4 0
INDIRP4
INDIRP4
ASGNP4
line 751
;750:
;751:	len = 0;
ADDRLP4 8
CNSTI4 0
ASGNI4
line 753
;752:
;753:	com_token[0] = 0;
ADDRGP4 com_token
CNSTI1 0
ASGNI1
line 759
;754:
;755:
;756:
;757:	// make sure incoming data is valid
;758:
;759:	if ( !data )
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $127
line 761
;760:
;761:	{
line 763
;762:
;763:		*data_p = NULL;
ADDRFP4 0
INDIRP4
CNSTP4 0
ASGNP4
line 765
;764:
;765:		return com_token;
ADDRGP4 com_token
RETP4
ADDRGP4 $123
JUMPV
LABELV $126
line 773
;766:
;767:	}
;768:
;769:
;770:
;771:	while ( 1 )
;772:
;773:	{
line 777
;774:
;775:		// skip whitespace
;776:
;777:		data = SkipWhitespace( data, &hasNewLines );
ADDRLP4 0
INDIRP4
ARGP4
ADDRLP4 12
ARGP4
ADDRLP4 16
ADDRGP4 SkipWhitespace
CALLP4
ASGNP4
ADDRLP4 0
ADDRLP4 16
INDIRP4
ASGNP4
line 779
;778:
;779:		if ( !data )
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $129
line 781
;780:
;781:		{
line 783
;782:
;783:			*data_p = NULL;
ADDRFP4 0
INDIRP4
CNSTP4 0
ASGNP4
line 785
;784:
;785:			return com_token;
ADDRGP4 com_token
RETP4
ADDRGP4 $123
JUMPV
LABELV $129
line 789
;786:
;787:		}
;788:
;789:		if ( hasNewLines && !allowLineBreaks )
ADDRLP4 20
CNSTI4 0
ASGNI4
ADDRLP4 12
INDIRI4
ADDRLP4 20
INDIRI4
EQI4 $131
ADDRFP4 4
INDIRI4
ADDRLP4 20
INDIRI4
NEI4 $131
line 791
;790:
;791:		{
line 793
;792:
;793:			*data_p = data;
ADDRFP4 0
INDIRP4
ADDRLP4 0
INDIRP4
ASGNP4
line 795
;794:
;795:			return com_token;
ADDRGP4 com_token
RETP4
ADDRGP4 $123
JUMPV
LABELV $131
line 801
;796:
;797:		}
;798:
;799:
;800:
;801:		c = *data;
ADDRLP4 4
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
line 807
;802:
;803:
;804:
;805:		// skip double slash comments
;806:
;807:		if ( c == '/' && data[1] == '/' )
ADDRLP4 24
CNSTI4 47
ASGNI4
ADDRLP4 4
INDIRI4
ADDRLP4 24
INDIRI4
NEI4 $133
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
INDIRI1
CVII4 1
ADDRLP4 24
INDIRI4
NEI4 $133
line 809
;808:
;809:		{
line 811
;810:
;811:			data += 2;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 2
ADDP4
ASGNP4
ADDRGP4 $136
JUMPV
LABELV $135
line 813
;812:
;813:			while (*data && *data != '\n') {
line 815
;814:
;815:				data++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 817
;816:
;817:		}
LABELV $136
line 813
ADDRLP4 28
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 28
INDIRI4
CNSTI4 0
EQI4 $138
ADDRLP4 28
INDIRI4
CNSTI4 10
NEI4 $135
LABELV $138
line 819
;818:
;819:		}
ADDRGP4 $134
JUMPV
LABELV $133
line 823
;820:
;821:		// skip /* */ comments
;822:
;823:		else if ( c=='/' && data[1] == '*' ) 
ADDRLP4 4
INDIRI4
CNSTI4 47
NEI4 $128
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
INDIRI1
CVII4 1
CNSTI4 42
NEI4 $128
line 825
;824:
;825:		{
line 827
;826:
;827:			data += 2;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 2
ADDP4
ASGNP4
ADDRGP4 $142
JUMPV
LABELV $141
line 831
;828:
;829:			while ( *data && ( *data != '*' || data[1] != '/' ) ) 
;830:
;831:			{
line 833
;832:
;833:				data++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 835
;834:
;835:			}
LABELV $142
line 829
ADDRLP4 32
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 32
INDIRI4
CNSTI4 0
EQI4 $144
ADDRLP4 32
INDIRI4
CNSTI4 42
NEI4 $141
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
INDIRI1
CVII4 1
CNSTI4 47
NEI4 $141
LABELV $144
line 837
;836:
;837:			if ( *data ) 
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
EQI4 $140
line 839
;838:
;839:			{
line 841
;840:
;841:				data += 2;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 2
ADDP4
ASGNP4
line 843
;842:
;843:			}
line 845
;844:
;845:		}
line 849
;846:
;847:		else
;848:
;849:		{
line 851
;850:
;851:			break;
LABELV $140
LABELV $134
line 855
;852:
;853:		}
;854:
;855:	}
LABELV $127
line 771
ADDRGP4 $126
JUMPV
LABELV $128
line 861
;856:
;857:
;858:
;859:	// handle quoted strings
;860:
;861:	if (c == '\"')
ADDRLP4 4
INDIRI4
CNSTI4 34
NEI4 $147
line 863
;862:
;863:	{
line 865
;864:
;865:		data++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRGP4 $150
JUMPV
LABELV $149
line 869
;866:
;867:		while (1)
;868:
;869:		{
line 871
;870:
;871:			c = *data++;
ADDRLP4 16
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 0
ADDRLP4 16
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 4
ADDRLP4 16
INDIRP4
INDIRI1
CVII4 1
ASGNI4
line 873
;872:
;873:			if (c=='\"' || !c)
ADDRLP4 4
INDIRI4
CNSTI4 34
EQI4 $154
ADDRLP4 4
INDIRI4
CNSTI4 0
NEI4 $152
LABELV $154
line 875
;874:
;875:			{
line 877
;876:
;877:				com_token[len] = 0;
ADDRLP4 8
INDIRI4
ADDRGP4 com_token
ADDP4
CNSTI1 0
ASGNI1
line 879
;878:
;879:				*data_p = ( char * ) data;
ADDRFP4 0
INDIRP4
ADDRLP4 0
INDIRP4
ASGNP4
line 881
;880:
;881:				return com_token;
ADDRGP4 com_token
RETP4
ADDRGP4 $123
JUMPV
LABELV $152
line 885
;882:
;883:			}
;884:
;885:			if (len < MAX_TOKEN_CHARS)
ADDRLP4 8
INDIRI4
CNSTI4 1024
GEI4 $155
line 887
;886:
;887:			{
line 889
;888:
;889:				com_token[len] = c;
ADDRLP4 8
INDIRI4
ADDRGP4 com_token
ADDP4
ADDRLP4 4
INDIRI4
CVII1 4
ASGNI1
line 891
;890:
;891:				len++;
ADDRLP4 8
ADDRLP4 8
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
line 893
;892:
;893:			}
LABELV $155
line 895
;894:
;895:		}
LABELV $150
line 867
ADDRGP4 $149
JUMPV
line 897
;896:
;897:	}
LABELV $147
LABELV $157
line 905
;898:
;899:
;900:
;901:	// parse a regular word
;902:
;903:	do
;904:
;905:	{
line 907
;906:
;907:		if (len < MAX_TOKEN_CHARS)
ADDRLP4 8
INDIRI4
CNSTI4 1024
GEI4 $160
line 909
;908:
;909:		{
line 911
;910:
;911:			com_token[len] = c;
ADDRLP4 8
INDIRI4
ADDRGP4 com_token
ADDP4
ADDRLP4 4
INDIRI4
CVII1 4
ASGNI1
line 913
;912:
;913:			len++;
ADDRLP4 8
ADDRLP4 8
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
line 915
;914:
;915:		}
LABELV $160
line 917
;916:
;917:		data++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 919
;918:
;919:		c = *data;
ADDRLP4 4
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
line 921
;920:
;921:		if ( c == '\n' )
ADDRLP4 4
INDIRI4
CNSTI4 10
NEI4 $162
line 923
;922:
;923:			com_lines++;
ADDRLP4 16
ADDRGP4 com_lines
ASGNP4
ADDRLP4 16
INDIRP4
ADDRLP4 16
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $162
line 925
;924:
;925:	} while (c>32);
LABELV $158
ADDRLP4 4
INDIRI4
CNSTI4 32
GTI4 $157
line 929
;926:
;927:
;928:
;929:	if (len == MAX_TOKEN_CHARS)
ADDRLP4 8
INDIRI4
CNSTI4 1024
NEI4 $164
line 931
;930:
;931:	{
line 935
;932:
;933://		Com_Printf ("Token exceeded %i chars, discarded.\n", MAX_TOKEN_CHARS);
;934:
;935:		len = 0;
ADDRLP4 8
CNSTI4 0
ASGNI4
line 937
;936:
;937:	}
LABELV $164
line 939
;938:
;939:	com_token[len] = 0;
ADDRLP4 8
INDIRI4
ADDRGP4 com_token
ADDP4
CNSTI1 0
ASGNI1
line 943
;940:
;941:
;942:
;943:	*data_p = ( char * ) data;
ADDRFP4 0
INDIRP4
ADDRLP4 0
INDIRP4
ASGNP4
line 945
;944:
;945:	return com_token;
ADDRGP4 com_token
RETP4
LABELV $123
endproc COM_ParseExt 36 8
export COM_MatchToken
proc COM_MatchToken 12 16
line 1073
;946:
;947:}
;948:
;949:
;950:
;951:
;952:
;953:#if 0
;954:
;955:// no longer used
;956:
;957:/*
;958:
;959:===============
;960:
;961:COM_ParseInfos
;962:
;963:===============
;964:
;965:*/
;966:
;967:int COM_ParseInfos( char *buf, int max, char infos[][MAX_INFO_STRING] ) {
;968:
;969:	char	*token;
;970:
;971:	int		count;
;972:
;973:	char	key[MAX_TOKEN_CHARS];
;974:
;975:
;976:
;977:	count = 0;
;978:
;979:
;980:
;981:	while ( 1 ) {
;982:
;983:		token = COM_Parse( &buf );
;984:
;985:		if ( !token[0] ) {
;986:
;987:			break;
;988:
;989:		}
;990:
;991:		if ( strcmp( token, "{" ) ) {
;992:
;993:			Com_Printf( "Missing { in info file\n" );
;994:
;995:			break;
;996:
;997:		}
;998:
;999:
;1000:
;1001:		if ( count == max ) {
;1002:
;1003:			Com_Printf( "Max infos exceeded\n" );
;1004:
;1005:			break;
;1006:
;1007:		}
;1008:
;1009:
;1010:
;1011:		infos[count][0] = 0;
;1012:
;1013:		while ( 1 ) {
;1014:
;1015:			token = COM_ParseExt( &buf, qtrue );
;1016:
;1017:			if ( !token[0] ) {
;1018:
;1019:				Com_Printf( "Unexpected end of info file\n" );
;1020:
;1021:				break;
;1022:
;1023:			}
;1024:
;1025:			if ( !strcmp( token, "}" ) ) {
;1026:
;1027:				break;
;1028:
;1029:			}
;1030:
;1031:			Q_strncpyz( key, token, sizeof( key ) );
;1032:
;1033:
;1034:
;1035:			token = COM_ParseExt( &buf, qfalse );
;1036:
;1037:			if ( !token[0] ) {
;1038:
;1039:				strcpy( token, "<NULL>" );
;1040:
;1041:			}
;1042:
;1043:			Info_SetValueForKey( infos[count], key, token );
;1044:
;1045:		}
;1046:
;1047:		count++;
;1048:
;1049:	}
;1050:
;1051:
;1052:
;1053:	return count;
;1054:
;1055:}
;1056:
;1057:#endif
;1058:
;1059:
;1060:
;1061:
;1062:
;1063:/*
;1064:
;1065:==================
;1066:
;1067:COM_MatchToken
;1068:
;1069:==================
;1070:
;1071:*/
;1072:
;1073:void COM_MatchToken( char **buf_p, char *match ) {
line 1079
;1074:
;1075:	char	*token;
;1076:
;1077:
;1078:
;1079:	token = COM_Parse( buf_p );
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 4
ADDRGP4 COM_Parse
CALLP4
ASGNP4
ADDRLP4 0
ADDRLP4 4
INDIRP4
ASGNP4
line 1081
;1080:
;1081:	if ( strcmp( token, match ) ) {
ADDRLP4 0
INDIRP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 8
ADDRGP4 strcmp
CALLI4
ASGNI4
ADDRLP4 8
INDIRI4
CNSTI4 0
EQI4 $167
line 1083
;1082:
;1083:		Com_Error( ERR_DROP, "MatchToken: %s != %s", token, match );
CNSTI4 1
ARGI4
ADDRGP4 $169
ARGP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 1085
;1084:
;1085:	}
LABELV $167
line 1087
;1086:
;1087:}
LABELV $166
endproc COM_MatchToken 12 16
export SkipBracedSection
proc SkipBracedSection 12 8
line 1111
;1088:
;1089:
;1090:
;1091:
;1092:
;1093:/*
;1094:
;1095:=================
;1096:
;1097:SkipBracedSection
;1098:
;1099:
;1100:
;1101:The next token should be an open brace.
;1102:
;1103:Skips until a matching close brace is found.
;1104:
;1105:Internal brace depths are properly skipped.
;1106:
;1107:=================
;1108:
;1109:*/
;1110:
;1111:void SkipBracedSection (char **program) {
line 1119
;1112:
;1113:	char			*token;
;1114:
;1115:	int				depth;
;1116:
;1117:
;1118:
;1119:	depth = 0;
ADDRLP4 4
CNSTI4 0
ASGNI4
LABELV $171
line 1121
;1120:
;1121:	do {
line 1123
;1122:
;1123:		token = COM_ParseExt( program, qtrue );
ADDRFP4 0
INDIRP4
ARGP4
CNSTI4 1
ARGI4
ADDRLP4 8
ADDRGP4 COM_ParseExt
CALLP4
ASGNP4
ADDRLP4 0
ADDRLP4 8
INDIRP4
ASGNP4
line 1125
;1124:
;1125:		if( token[1] == 0 ) {
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $174
line 1127
;1126:
;1127:			if( token[0] == '{' ) {
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 123
NEI4 $176
line 1129
;1128:
;1129:				depth++;
ADDRLP4 4
ADDRLP4 4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
line 1131
;1130:
;1131:			}
ADDRGP4 $177
JUMPV
LABELV $176
line 1133
;1132:
;1133:			else if( token[0] == '}' ) {
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 125
NEI4 $178
line 1135
;1134:
;1135:				depth--;
ADDRLP4 4
ADDRLP4 4
INDIRI4
CNSTI4 1
SUBI4
ASGNI4
line 1137
;1136:
;1137:			}
LABELV $178
LABELV $177
line 1139
;1138:
;1139:		}
LABELV $174
line 1141
;1140:
;1141:	} while( depth && *program );
LABELV $172
ADDRLP4 4
INDIRI4
CNSTI4 0
EQI4 $180
ADDRFP4 0
INDIRP4
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $171
LABELV $180
line 1143
;1142:
;1143:}
LABELV $170
endproc SkipBracedSection 12 8
export SkipRestOfLine
proc SkipRestOfLine 16 0
line 1157
;1144:
;1145:
;1146:
;1147:/*
;1148:
;1149:=================
;1150:
;1151:SkipRestOfLine
;1152:
;1153:=================
;1154:
;1155:*/
;1156:
;1157:void SkipRestOfLine ( char **data ) {
line 1165
;1158:
;1159:	char	*p;
;1160:
;1161:	int		c;
;1162:
;1163:
;1164:
;1165:	p = *data;
ADDRLP4 4
ADDRFP4 0
INDIRP4
INDIRP4
ASGNP4
ADDRGP4 $183
JUMPV
LABELV $182
line 1167
;1166:
;1167:	while ( (c = *p++) != 0 ) {
line 1169
;1168:
;1169:		if ( c == '\n' ) {
ADDRLP4 0
INDIRI4
CNSTI4 10
NEI4 $185
line 1171
;1170:
;1171:			com_lines++;
ADDRLP4 8
ADDRGP4 com_lines
ASGNP4
ADDRLP4 8
INDIRP4
ADDRLP4 8
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
line 1173
;1172:
;1173:			break;
ADDRGP4 $184
JUMPV
LABELV $185
line 1177
;1174:
;1175:		}
;1176:
;1177:	}
LABELV $183
line 1167
ADDRLP4 8
ADDRLP4 4
INDIRP4
ASGNP4
ADDRLP4 4
ADDRLP4 8
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 12
ADDRLP4 8
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 0
ADDRLP4 12
INDIRI4
ASGNI4
ADDRLP4 12
INDIRI4
CNSTI4 0
NEI4 $182
LABELV $184
line 1181
;1178:
;1179:
;1180:
;1181:	*data = p;
ADDRFP4 0
INDIRP4
ADDRLP4 4
INDIRP4
ASGNP4
line 1183
;1182:
;1183:}
LABELV $181
endproc SkipRestOfLine 16 0
export Parse1DMatrix
proc Parse1DMatrix 16 8
line 1189
;1184:
;1185:
;1186:
;1187:
;1188:
;1189:void Parse1DMatrix (char **buf_p, int x, float *m) {
line 1197
;1190:
;1191:	char	*token;
;1192:
;1193:	int		i;
;1194:
;1195:
;1196:
;1197:	COM_MatchToken( buf_p, "(" );
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 $188
ARGP4
ADDRGP4 COM_MatchToken
CALLV
pop
line 1201
;1198:
;1199:
;1200:
;1201:	for (i = 0 ; i < x ; i++) {
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $192
JUMPV
LABELV $189
line 1203
;1202:
;1203:		token = COM_Parse(buf_p);
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 8
ADDRGP4 COM_Parse
CALLP4
ASGNP4
ADDRLP4 4
ADDRLP4 8
INDIRP4
ASGNP4
line 1205
;1204:
;1205:		m[i] = atof(token);
ADDRLP4 4
INDIRP4
ARGP4
ADDRLP4 12
ADDRGP4 atof
CALLF4
ASGNF4
ADDRLP4 0
INDIRI4
CNSTI4 2
LSHI4
ADDRFP4 8
INDIRP4
ADDP4
ADDRLP4 12
INDIRF4
ASGNF4
line 1207
;1206:
;1207:	}
LABELV $190
line 1201
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $192
ADDRLP4 0
INDIRI4
ADDRFP4 4
INDIRI4
LTI4 $189
line 1211
;1208:
;1209:
;1210:
;1211:	COM_MatchToken( buf_p, ")" );
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 $193
ARGP4
ADDRGP4 COM_MatchToken
CALLV
pop
line 1213
;1212:
;1213:}
LABELV $187
endproc Parse1DMatrix 16 8
export Parse2DMatrix
proc Parse2DMatrix 8 12
line 1217
;1214:
;1215:
;1216:
;1217:void Parse2DMatrix (char **buf_p, int y, int x, float *m) {
line 1223
;1218:
;1219:	int		i;
;1220:
;1221:
;1222:
;1223:	COM_MatchToken( buf_p, "(" );
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 $188
ARGP4
ADDRGP4 COM_MatchToken
CALLV
pop
line 1227
;1224:
;1225:
;1226:
;1227:	for (i = 0 ; i < y ; i++) {
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $198
JUMPV
LABELV $195
line 1229
;1228:
;1229:		Parse1DMatrix (buf_p, x, m + i * x);
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 4
ADDRFP4 8
INDIRI4
ASGNI4
ADDRLP4 4
INDIRI4
ARGI4
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRI4
MULI4
CNSTI4 2
LSHI4
ADDRFP4 12
INDIRP4
ADDP4
ARGP4
ADDRGP4 Parse1DMatrix
CALLV
pop
line 1231
;1230:
;1231:	}
LABELV $196
line 1227
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $198
ADDRLP4 0
INDIRI4
ADDRFP4 4
INDIRI4
LTI4 $195
line 1235
;1232:
;1233:
;1234:
;1235:	COM_MatchToken( buf_p, ")" );
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 $193
ARGP4
ADDRGP4 COM_MatchToken
CALLV
pop
line 1237
;1236:
;1237:}
LABELV $194
endproc Parse2DMatrix 8 12
export Parse3DMatrix
proc Parse3DMatrix 12 16
line 1241
;1238:
;1239:
;1240:
;1241:void Parse3DMatrix (char **buf_p, int z, int y, int x, float *m) {
line 1247
;1242:
;1243:	int		i;
;1244:
;1245:
;1246:
;1247:	COM_MatchToken( buf_p, "(" );
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 $188
ARGP4
ADDRGP4 COM_MatchToken
CALLV
pop
line 1251
;1248:
;1249:
;1250:
;1251:	for (i = 0 ; i < z ; i++) {
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $203
JUMPV
LABELV $200
line 1253
;1252:
;1253:		Parse2DMatrix (buf_p, y, x, m + i * x*y);
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 4
ADDRFP4 8
INDIRI4
ASGNI4
ADDRLP4 4
INDIRI4
ARGI4
ADDRLP4 8
ADDRFP4 12
INDIRI4
ASGNI4
ADDRLP4 8
INDIRI4
ARGI4
ADDRLP4 0
INDIRI4
ADDRLP4 8
INDIRI4
MULI4
ADDRLP4 4
INDIRI4
MULI4
CNSTI4 2
LSHI4
ADDRFP4 16
INDIRP4
ADDP4
ARGP4
ADDRGP4 Parse2DMatrix
CALLV
pop
line 1255
;1254:
;1255:	}
LABELV $201
line 1251
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $203
ADDRLP4 0
INDIRI4
ADDRFP4 4
INDIRI4
LTI4 $200
line 1259
;1256:
;1257:
;1258:
;1259:	COM_MatchToken( buf_p, ")" );
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 $193
ARGP4
ADDRGP4 COM_MatchToken
CALLV
pop
line 1261
;1260:
;1261:}
LABELV $199
endproc Parse3DMatrix 12 16
export Q_isprint
proc Q_isprint 4 0
line 1285
;1262:
;1263:
;1264:
;1265:
;1266:
;1267:/*
;1268:
;1269:============================================================================
;1270:
;1271:
;1272:
;1273:					LIBRARY REPLACEMENT FUNCTIONS
;1274:
;1275:
;1276:
;1277:============================================================================
;1278:
;1279:*/
;1280:
;1281:
;1282:
;1283:int Q_isprint( int c )
;1284:
;1285:{
line 1287
;1286:
;1287:	if ( c >= 0x20 && c <= 0x7E )
ADDRLP4 0
ADDRFP4 0
INDIRI4
ASGNI4
ADDRLP4 0
INDIRI4
CNSTI4 32
LTI4 $205
ADDRLP4 0
INDIRI4
CNSTI4 126
GTI4 $205
line 1289
;1288:
;1289:		return ( 1 );
CNSTI4 1
RETI4
ADDRGP4 $204
JUMPV
LABELV $205
line 1291
;1290:
;1291:	return ( 0 );
CNSTI4 0
RETI4
LABELV $204
endproc Q_isprint 4 0
export Q_islower
proc Q_islower 4 0
line 1299
;1292:
;1293:}
;1294:
;1295:
;1296:
;1297:int Q_islower( int c )
;1298:
;1299:{
line 1301
;1300:
;1301:	if (c >= 'a' && c <= 'z')
ADDRLP4 0
ADDRFP4 0
INDIRI4
ASGNI4
ADDRLP4 0
INDIRI4
CNSTI4 97
LTI4 $208
ADDRLP4 0
INDIRI4
CNSTI4 122
GTI4 $208
line 1303
;1302:
;1303:		return ( 1 );
CNSTI4 1
RETI4
ADDRGP4 $207
JUMPV
LABELV $208
line 1305
;1304:
;1305:	return ( 0 );
CNSTI4 0
RETI4
LABELV $207
endproc Q_islower 4 0
export Q_isupper
proc Q_isupper 4 0
line 1313
;1306:
;1307:}
;1308:
;1309:
;1310:
;1311:int Q_isupper( int c )
;1312:
;1313:{
line 1315
;1314:
;1315:	if (c >= 'A' && c <= 'Z')
ADDRLP4 0
ADDRFP4 0
INDIRI4
ASGNI4
ADDRLP4 0
INDIRI4
CNSTI4 65
LTI4 $211
ADDRLP4 0
INDIRI4
CNSTI4 90
GTI4 $211
line 1317
;1316:
;1317:		return ( 1 );
CNSTI4 1
RETI4
ADDRGP4 $210
JUMPV
LABELV $211
line 1319
;1318:
;1319:	return ( 0 );
CNSTI4 0
RETI4
LABELV $210
endproc Q_isupper 4 0
export Q_isalpha
proc Q_isalpha 8 0
line 1327
;1320:
;1321:}
;1322:
;1323:
;1324:
;1325:int Q_isalpha( int c )
;1326:
;1327:{
line 1329
;1328:
;1329:	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
ADDRLP4 0
ADDRFP4 0
INDIRI4
ASGNI4
ADDRLP4 0
INDIRI4
CNSTI4 97
LTI4 $217
ADDRLP4 0
INDIRI4
CNSTI4 122
LEI4 $216
LABELV $217
ADDRLP4 4
ADDRFP4 0
INDIRI4
ASGNI4
ADDRLP4 4
INDIRI4
CNSTI4 65
LTI4 $214
ADDRLP4 4
INDIRI4
CNSTI4 90
GTI4 $214
LABELV $216
line 1331
;1330:
;1331:		return ( 1 );
CNSTI4 1
RETI4
ADDRGP4 $213
JUMPV
LABELV $214
line 1333
;1332:
;1333:	return ( 0 );
CNSTI4 0
RETI4
LABELV $213
endproc Q_isalpha 8 0
export Q_strrchr
proc Q_strrchr 12 0
line 1341
;1334:
;1335:}
;1336:
;1337:
;1338:
;1339:char* Q_strrchr( const char* string, int c )
;1340:
;1341:{
line 1343
;1342:
;1343:	char cc = c;
ADDRLP4 4
ADDRFP4 4
INDIRI4
CVII1 4
ASGNI1
line 1347
;1344:
;1345:	char *s;
;1346:
;1347:	char *sp=(char *)0;
ADDRLP4 8
CNSTP4 0
ASGNP4
line 1351
;1348:
;1349:
;1350:
;1351:	s = (char*)string;
ADDRLP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRGP4 $220
JUMPV
LABELV $219
line 1357
;1352:
;1353:
;1354:
;1355:	while (*s)
;1356:
;1357:	{
line 1359
;1358:
;1359:		if (*s == cc)
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ADDRLP4 4
INDIRI1
CVII4 1
NEI4 $222
line 1361
;1360:
;1361:			sp = s;
ADDRLP4 8
ADDRLP4 0
INDIRP4
ASGNP4
LABELV $222
line 1363
;1362:
;1363:		s++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 1365
;1364:
;1365:	}
LABELV $220
line 1355
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $219
line 1367
;1366:
;1367:	if (cc == 0)
ADDRLP4 4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $224
line 1369
;1368:
;1369:		sp = s;
ADDRLP4 8
ADDRLP4 0
INDIRP4
ASGNP4
LABELV $224
line 1373
;1370:
;1371:
;1372:
;1373:	return sp;
ADDRLP4 8
INDIRP4
RETP4
LABELV $218
endproc Q_strrchr 12 0
export Q_strncpyz
proc Q_strncpyz 0 12
line 1393
;1374:
;1375:}
;1376:
;1377:
;1378:
;1379:/*
;1380:
;1381:=============
;1382:
;1383:Q_strncpyz
;1384:
;1385: 
;1386:
;1387:Safe strncpy that ensures a trailing zero
;1388:
;1389:=============
;1390:
;1391:*/
;1392:
;1393:void Q_strncpyz( char *dest, const char *src, int destsize ) {
line 1397
;1394:
;1395:  // bk001129 - also NULL dest
;1396:
;1397:  if ( !dest ) {
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $227
line 1399
;1398:
;1399:    Com_Error( ERR_FATAL, "Q_strncpyz: NULL dest" );
CNSTI4 0
ARGI4
ADDRGP4 $229
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 1401
;1400:
;1401:  }
LABELV $227
line 1403
;1402:
;1403:	if ( !src ) {
ADDRFP4 4
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $230
line 1405
;1404:
;1405:		Com_Error( ERR_FATAL, "Q_strncpyz: NULL src" );
CNSTI4 0
ARGI4
ADDRGP4 $232
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 1407
;1406:
;1407:	}
LABELV $230
line 1409
;1408:
;1409:	if ( destsize < 1 ) {
ADDRFP4 8
INDIRI4
CNSTI4 1
GEI4 $233
line 1411
;1410:
;1411:		Com_Error(ERR_FATAL,"Q_strncpyz: destsize < 1" ); 
CNSTI4 0
ARGI4
ADDRGP4 $235
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 1413
;1412:
;1413:	}
LABELV $233
line 1417
;1414:
;1415:
;1416:
;1417:	strncpy( dest, src, destsize-1 );
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRFP4 8
INDIRI4
CNSTI4 1
SUBI4
ARGI4
ADDRGP4 strncpy
CALLP4
pop
line 1419
;1418:
;1419:    dest[destsize-1] = 0;
ADDRFP4 8
INDIRI4
CNSTI4 1
SUBI4
ADDRFP4 0
INDIRP4
ADDP4
CNSTI1 0
ASGNI1
line 1421
;1420:
;1421:}
LABELV $226
endproc Q_strncpyz 0 12
export Q_stricmpn
proc Q_stricmpn 32 0
line 1425
;1422:
;1423:                 
;1424:
;1425:int Q_stricmpn (const char *s1, const char *s2, int n) {
line 1433
;1426:
;1427:	int		c1, c2;
;1428:
;1429:	
;1430:
;1431:	// bk001129 - moved in 1.17 fix not in id codebase
;1432:
;1433:        if ( s1 == NULL ) {
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $237
line 1435
;1434:
;1435:           if ( s2 == NULL )
ADDRFP4 4
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $239
line 1437
;1436:
;1437:             return 0;
CNSTI4 0
RETI4
ADDRGP4 $236
JUMPV
LABELV $239
line 1441
;1438:
;1439:           else
;1440:
;1441:             return -1;
CNSTI4 -1
RETI4
ADDRGP4 $236
JUMPV
LABELV $237
line 1445
;1442:
;1443:        }
;1444:
;1445:        else if ( s2==NULL )
ADDRFP4 4
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $241
line 1447
;1446:
;1447:          return 1;
CNSTI4 1
RETI4
ADDRGP4 $236
JUMPV
LABELV $241
LABELV $243
line 1455
;1448:
;1449:
;1450:
;1451:
;1452:
;1453:	
;1454:
;1455:	do {
line 1457
;1456:
;1457:		c1 = *s1++;
ADDRLP4 8
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
ADDRLP4 8
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 0
ADDRLP4 8
INDIRP4
INDIRI1
CVII4 1
ASGNI4
line 1459
;1458:
;1459:		c2 = *s2++;
ADDRLP4 12
ADDRFP4 4
INDIRP4
ASGNP4
ADDRFP4 4
ADDRLP4 12
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 4
ADDRLP4 12
INDIRP4
INDIRI1
CVII4 1
ASGNI4
line 1463
;1460:
;1461:
;1462:
;1463:		if (!n--) {
ADDRLP4 16
ADDRFP4 8
INDIRI4
ASGNI4
ADDRFP4 8
ADDRLP4 16
INDIRI4
CNSTI4 1
SUBI4
ASGNI4
ADDRLP4 16
INDIRI4
CNSTI4 0
NEI4 $246
line 1465
;1464:
;1465:			return 0;		// strings are equal until end point
CNSTI4 0
RETI4
ADDRGP4 $236
JUMPV
LABELV $246
line 1471
;1466:
;1467:		}
;1468:
;1469:		
;1470:
;1471:		if (c1 != c2) {
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRI4
EQI4 $248
line 1473
;1472:
;1473:			if (c1 >= 'a' && c1 <= 'z') {
ADDRLP4 0
INDIRI4
CNSTI4 97
LTI4 $250
ADDRLP4 0
INDIRI4
CNSTI4 122
GTI4 $250
line 1475
;1474:
;1475:				c1 -= ('a' - 'A');
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 32
SUBI4
ASGNI4
line 1477
;1476:
;1477:			}
LABELV $250
line 1479
;1478:
;1479:			if (c2 >= 'a' && c2 <= 'z') {
ADDRLP4 4
INDIRI4
CNSTI4 97
LTI4 $252
ADDRLP4 4
INDIRI4
CNSTI4 122
GTI4 $252
line 1481
;1480:
;1481:				c2 -= ('a' - 'A');
ADDRLP4 4
ADDRLP4 4
INDIRI4
CNSTI4 32
SUBI4
ASGNI4
line 1483
;1482:
;1483:			}
LABELV $252
line 1485
;1484:
;1485:			if (c1 != c2) {
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRI4
EQI4 $254
line 1487
;1486:
;1487:				return c1 < c2 ? -1 : 1;
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRI4
GEI4 $257
ADDRLP4 28
CNSTI4 -1
ASGNI4
ADDRGP4 $258
JUMPV
LABELV $257
ADDRLP4 28
CNSTI4 1
ASGNI4
LABELV $258
ADDRLP4 28
INDIRI4
RETI4
ADDRGP4 $236
JUMPV
LABELV $254
line 1491
;1488:
;1489:			}
;1490:
;1491:		}
LABELV $248
line 1493
;1492:
;1493:	} while (c1);
LABELV $244
ADDRLP4 0
INDIRI4
CNSTI4 0
NEI4 $243
line 1497
;1494:
;1495:	
;1496:
;1497:	return 0;		// strings are equal
CNSTI4 0
RETI4
LABELV $236
endproc Q_stricmpn 32 0
export Q_strncmp
proc Q_strncmp 24 0
line 1503
;1498:
;1499:}
;1500:
;1501:
;1502:
;1503:int Q_strncmp (const char *s1, const char *s2, int n) {
LABELV $260
line 1509
;1504:
;1505:	int		c1, c2;
;1506:
;1507:	
;1508:
;1509:	do {
line 1511
;1510:
;1511:		c1 = *s1++;
ADDRLP4 8
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
ADDRLP4 8
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 0
ADDRLP4 8
INDIRP4
INDIRI1
CVII4 1
ASGNI4
line 1513
;1512:
;1513:		c2 = *s2++;
ADDRLP4 12
ADDRFP4 4
INDIRP4
ASGNP4
ADDRFP4 4
ADDRLP4 12
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 4
ADDRLP4 12
INDIRP4
INDIRI1
CVII4 1
ASGNI4
line 1517
;1514:
;1515:
;1516:
;1517:		if (!n--) {
ADDRLP4 16
ADDRFP4 8
INDIRI4
ASGNI4
ADDRFP4 8
ADDRLP4 16
INDIRI4
CNSTI4 1
SUBI4
ASGNI4
ADDRLP4 16
INDIRI4
CNSTI4 0
NEI4 $263
line 1519
;1518:
;1519:			return 0;		// strings are equal until end point
CNSTI4 0
RETI4
ADDRGP4 $259
JUMPV
LABELV $263
line 1525
;1520:
;1521:		}
;1522:
;1523:		
;1524:
;1525:		if (c1 != c2) {
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRI4
EQI4 $265
line 1527
;1526:
;1527:			return c1 < c2 ? -1 : 1;
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRI4
GEI4 $268
ADDRLP4 20
CNSTI4 -1
ASGNI4
ADDRGP4 $269
JUMPV
LABELV $268
ADDRLP4 20
CNSTI4 1
ASGNI4
LABELV $269
ADDRLP4 20
INDIRI4
RETI4
ADDRGP4 $259
JUMPV
LABELV $265
line 1531
;1528:
;1529:		}
;1530:
;1531:	} while (c1);
LABELV $261
ADDRLP4 0
INDIRI4
CNSTI4 0
NEI4 $260
line 1535
;1532:
;1533:	
;1534:
;1535:	return 0;		// strings are equal
CNSTI4 0
RETI4
LABELV $259
endproc Q_strncmp 24 0
export Q_stricmp
proc Q_stricmp 12 12
line 1541
;1536:
;1537:}
;1538:
;1539:
;1540:
;1541:int Q_stricmp (const char *s1, const char *s2) {
line 1543
;1542:
;1543:	return (s1 && s2) ? Q_stricmpn (s1, s2, 99999) : -1;
ADDRLP4 4
CNSTU4 0
ASGNU4
ADDRFP4 0
INDIRP4
CVPU4 4
ADDRLP4 4
INDIRU4
EQU4 $272
ADDRFP4 4
INDIRP4
CVPU4 4
ADDRLP4 4
INDIRU4
EQU4 $272
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
CNSTI4 99999
ARGI4
ADDRLP4 8
ADDRGP4 Q_stricmpn
CALLI4
ASGNI4
ADDRLP4 0
ADDRLP4 8
INDIRI4
ASGNI4
ADDRGP4 $273
JUMPV
LABELV $272
ADDRLP4 0
CNSTI4 -1
ASGNI4
LABELV $273
ADDRLP4 0
INDIRI4
RETI4
LABELV $270
endproc Q_stricmp 12 12
export Q_strlwr
proc Q_strlwr 12 4
line 1551
;1544:
;1545:}
;1546:
;1547:
;1548:
;1549:
;1550:
;1551:char *Q_strlwr( char *s1 ) {
line 1557
;1552:
;1553:    char	*s;
;1554:
;1555:
;1556:
;1557:    s = s1;
ADDRLP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRGP4 $276
JUMPV
LABELV $275
line 1559
;1558:
;1559:	while ( *s ) {
line 1561
;1560:
;1561:		*s = tolower(*s);
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ARGI4
ADDRLP4 8
ADDRGP4 tolower
CALLI4
ASGNI4
ADDRLP4 0
INDIRP4
ADDRLP4 8
INDIRI4
CVII1 4
ASGNI1
line 1563
;1562:
;1563:		s++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 1565
;1564:
;1565:	}
LABELV $276
line 1559
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $275
line 1567
;1566:
;1567:    return s1;
ADDRFP4 0
INDIRP4
RETP4
LABELV $274
endproc Q_strlwr 12 4
export Q_strupr
proc Q_strupr 12 4
line 1573
;1568:
;1569:}
;1570:
;1571:
;1572:
;1573:char *Q_strupr( char *s1 ) {
line 1579
;1574:
;1575:    char	*s;
;1576:
;1577:
;1578:
;1579:    s = s1;
ADDRLP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRGP4 $280
JUMPV
LABELV $279
line 1581
;1580:
;1581:	while ( *s ) {
line 1583
;1582:
;1583:		*s = toupper(*s);
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ARGI4
ADDRLP4 8
ADDRGP4 toupper
CALLI4
ASGNI4
ADDRLP4 0
INDIRP4
ADDRLP4 8
INDIRI4
CVII1 4
ASGNI1
line 1585
;1584:
;1585:		s++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 1587
;1586:
;1587:	}
LABELV $280
line 1581
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $279
line 1589
;1588:
;1589:    return s1;
ADDRFP4 0
INDIRP4
RETP4
LABELV $278
endproc Q_strupr 12 4
export Q_strcat
proc Q_strcat 12 12
line 1599
;1590:
;1591:}
;1592:
;1593:
;1594:
;1595:
;1596:
;1597:// never goes past bounds or leaves without a terminating 0
;1598:
;1599:void Q_strcat( char *dest, int size, const char *src ) {
line 1605
;1600:
;1601:	int		l1;
;1602:
;1603:
;1604:
;1605:	l1 = strlen( dest );
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 4
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 0
ADDRLP4 4
INDIRI4
ASGNI4
line 1607
;1606:
;1607:	if ( l1 >= size ) {
ADDRLP4 0
INDIRI4
ADDRFP4 4
INDIRI4
LTI4 $283
line 1609
;1608:
;1609:		Com_Error( ERR_FATAL, "Q_strcat: already overflowed" );
CNSTI4 0
ARGI4
ADDRGP4 $285
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 1611
;1610:
;1611:	}
LABELV $283
line 1613
;1612:
;1613:	Q_strncpyz( dest + l1, src, size - l1 );
ADDRLP4 0
INDIRI4
ADDRFP4 0
INDIRP4
ADDP4
ARGP4
ADDRFP4 8
INDIRP4
ARGP4
ADDRFP4 4
INDIRI4
ADDRLP4 0
INDIRI4
SUBI4
ARGI4
ADDRGP4 Q_strncpyz
CALLV
pop
line 1615
;1614:
;1615:}
LABELV $282
endproc Q_strcat 12 12
export Q_PrintStrlen
proc Q_PrintStrlen 20 0
line 1621
;1616:
;1617:
;1618:
;1619:
;1620:
;1621:int Q_PrintStrlen( const char *string ) {
line 1629
;1622:
;1623:	int			len;
;1624:
;1625:	const char	*p;
;1626:
;1627:
;1628:
;1629:	if( !string ) {
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $287
line 1631
;1630:
;1631:		return 0;
CNSTI4 0
RETI4
ADDRGP4 $286
JUMPV
LABELV $287
line 1637
;1632:
;1633:	}
;1634:
;1635:
;1636:
;1637:	len = 0;
ADDRLP4 4
CNSTI4 0
ASGNI4
line 1639
;1638:
;1639:	p = string;
ADDRLP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRGP4 $290
JUMPV
LABELV $289
line 1641
;1640:
;1641:	while( *p ) {
line 1643
;1642:
;1643:		if( Q_IsColorString( p ) ) {
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $292
ADDRLP4 12
CNSTI4 94
ASGNI4
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ADDRLP4 12
INDIRI4
NEI4 $292
ADDRLP4 16
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 16
INDIRI4
CNSTI4 0
EQI4 $292
ADDRLP4 16
INDIRI4
ADDRLP4 12
INDIRI4
EQI4 $292
line 1645
;1644:
;1645:			p += 2;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 2
ADDP4
ASGNP4
line 1647
;1646:
;1647:			continue;
ADDRGP4 $290
JUMPV
LABELV $292
line 1651
;1648:
;1649:		}
;1650:
;1651:		p++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 1653
;1652:
;1653:		len++;
ADDRLP4 4
ADDRLP4 4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
line 1655
;1654:
;1655:	}
LABELV $290
line 1641
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $289
line 1659
;1656:
;1657:
;1658:
;1659:	return len;
ADDRLP4 4
INDIRI4
RETI4
LABELV $286
endproc Q_PrintStrlen 20 0
export Q_CleanStr
proc Q_CleanStr 32 0
line 1667
;1660:
;1661:}
;1662:
;1663:
;1664:
;1665:
;1666:
;1667:char *Q_CleanStr( char *string ) {
line 1677
;1668:
;1669:	char*	d;
;1670:
;1671:	char*	s;
;1672:
;1673:	int		c;
;1674:
;1675:
;1676:
;1677:	s = string;
ADDRLP4 0
ADDRFP4 0
INDIRP4
ASGNP4
line 1679
;1678:
;1679:	d = string;
ADDRLP4 8
ADDRFP4 0
INDIRP4
ASGNP4
ADDRGP4 $296
JUMPV
LABELV $295
line 1681
;1680:
;1681:	while ((c = *s) != 0 ) {
line 1683
;1682:
;1683:		if ( Q_IsColorString( s ) ) {
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $298
ADDRLP4 16
CNSTI4 94
ASGNI4
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ADDRLP4 16
INDIRI4
NEI4 $298
ADDRLP4 20
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 20
INDIRI4
CNSTI4 0
EQI4 $298
ADDRLP4 20
INDIRI4
ADDRLP4 16
INDIRI4
EQI4 $298
line 1685
;1684:
;1685:			s++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 1687
;1686:
;1687:		}		
ADDRGP4 $299
JUMPV
LABELV $298
line 1689
;1688:
;1689:		else if ( c >= 0x20 && c <= 0x7E ) {
ADDRLP4 4
INDIRI4
CNSTI4 32
LTI4 $300
ADDRLP4 4
INDIRI4
CNSTI4 126
GTI4 $300
line 1691
;1690:
;1691:			*d++ = c;
ADDRLP4 28
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 28
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 28
INDIRP4
ADDRLP4 4
INDIRI4
CVII1 4
ASGNI1
line 1693
;1692:
;1693:		}
LABELV $300
LABELV $299
line 1695
;1694:
;1695:		s++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 1697
;1696:
;1697:	}
LABELV $296
line 1681
ADDRLP4 12
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 4
ADDRLP4 12
INDIRI4
ASGNI4
ADDRLP4 12
INDIRI4
CNSTI4 0
NEI4 $295
line 1699
;1698:
;1699:	*d = '\0';
ADDRLP4 8
INDIRP4
CNSTI1 0
ASGNI1
line 1703
;1700:
;1701:
;1702:
;1703:	return string;
ADDRFP4 0
INDIRP4
RETP4
LABELV $294
endproc Q_CleanStr 32 0
export Com_sprintf
proc Com_sprintf 32012 12
line 1711
;1704:
;1705:}
;1706:
;1707:
;1708:
;1709:
;1710:
;1711:void QDECL Com_sprintf( char *dest, int size, const char *fmt, ...) {
line 1721
;1712:
;1713:	int		len;
;1714:
;1715:	va_list		argptr;
;1716:
;1717:	char	bigbuffer[32000];	// big, but small enough to fit in PPC stack
;1718:
;1719:
;1720:
;1721:	va_start (argptr,fmt);
ADDRLP4 4
ADDRFP4 8+4
ASGNP4
line 1723
;1722:
;1723:	len = vsprintf (bigbuffer,fmt,argptr);
ADDRLP4 8
ARGP4
ADDRFP4 8
INDIRP4
ARGP4
ADDRLP4 4
INDIRP4
ARGP4
ADDRLP4 32008
ADDRGP4 vsprintf
CALLI4
ASGNI4
ADDRLP4 0
ADDRLP4 32008
INDIRI4
ASGNI4
line 1725
;1724:
;1725:	va_end (argptr);
ADDRLP4 4
CNSTP4 0
ASGNP4
line 1727
;1726:
;1727:	if ( len >= sizeof( bigbuffer ) ) {
ADDRLP4 0
INDIRI4
CVIU4 4
CNSTU4 32000
LTU4 $304
line 1729
;1728:
;1729:		Com_Error( ERR_FATAL, "Com_sprintf: overflowed bigbuffer" );
CNSTI4 0
ARGI4
ADDRGP4 $306
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 1731
;1730:
;1731:	}
LABELV $304
line 1733
;1732:
;1733:	if (len >= size) {
ADDRLP4 0
INDIRI4
ADDRFP4 4
INDIRI4
LTI4 $307
line 1735
;1734:
;1735:		Com_Printf ("Com_sprintf: overflow of %i in %i\n", len, size);
ADDRGP4 $309
ARGP4
ADDRLP4 0
INDIRI4
ARGI4
ADDRFP4 4
INDIRI4
ARGI4
ADDRGP4 Com_Printf
CALLV
pop
line 1747
;1736:
;1737:#ifdef	_DEBUG
;1738:
;1739:		__asm {
;1740:
;1741:			int 3;
;1742:
;1743:		}
;1744:
;1745:#endif
;1746:
;1747:	}
LABELV $307
line 1749
;1748:
;1749:	Q_strncpyz (dest, bigbuffer, size );
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 8
ARGP4
ADDRFP4 4
INDIRI4
ARGI4
ADDRGP4 Q_strncpyz
CALLV
pop
line 1751
;1750:
;1751:}
LABELV $302
endproc Com_sprintf 32012 12
bss
align 1
LABELV $311
skip 64000
data
align 4
LABELV $312
byte 4 0
export va
code
proc va 12 12
line 1775
;1752:
;1753:
;1754:
;1755:
;1756:
;1757:/*
;1758:
;1759:============
;1760:
;1761:va
;1762:
;1763:
;1764:
;1765:does a varargs printf into a temp buffer, so I don't need to have
;1766:
;1767:varargs versions of all text functions.
;1768:
;1769:FIXME: make this buffer size safe someday
;1770:
;1771:============
;1772:
;1773:*/
;1774:
;1775:char	* QDECL va( char *format, ... ) {
line 1787
;1776:
;1777:	va_list		argptr;
;1778:
;1779:	static char		string[2][32000];	// in case va is called by nested functions
;1780:
;1781:	static int		index = 0;
;1782:
;1783:	char	*buf;
;1784:
;1785:
;1786:
;1787:	buf = string[index & 1];
ADDRLP4 4
CNSTI4 32000
ADDRGP4 $312
INDIRI4
CNSTI4 1
BANDI4
MULI4
ADDRGP4 $311
ADDP4
ASGNP4
line 1789
;1788:
;1789:	index++;
ADDRLP4 8
ADDRGP4 $312
ASGNP4
ADDRLP4 8
INDIRP4
ADDRLP4 8
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
line 1793
;1790:
;1791:
;1792:
;1793:	va_start (argptr, format);
ADDRLP4 0
ADDRFP4 0+4
ASGNP4
line 1795
;1794:
;1795:	vsprintf (buf, format,argptr);
ADDRLP4 4
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 vsprintf
CALLI4
pop
line 1797
;1796:
;1797:	va_end (argptr);
ADDRLP4 0
CNSTP4 0
ASGNP4
line 1801
;1798:
;1799:
;1800:
;1801:	return buf;
ADDRLP4 4
INDIRP4
RETP4
LABELV $310
endproc va 12 12
bss
align 1
LABELV $315
skip 16384
data
align 4
LABELV $316
byte 4 0
export Info_ValueForKey
code
proc Info_ValueForKey 8220 8
line 1843
;1802:
;1803:}
;1804:
;1805:
;1806:
;1807:
;1808:
;1809:/*
;1810:
;1811:=====================================================================
;1812:
;1813:
;1814:
;1815:  INFO STRINGS
;1816:
;1817:
;1818:
;1819:=====================================================================
;1820:
;1821:*/
;1822:
;1823:
;1824:
;1825:/*
;1826:
;1827:===============
;1828:
;1829:Info_ValueForKey
;1830:
;1831:
;1832:
;1833:Searches the string for the given
;1834:
;1835:key and returns the associated value, or an empty string.
;1836:
;1837:FIXME: overflow check?
;1838:
;1839:===============
;1840:
;1841:*/
;1842:
;1843:char *Info_ValueForKey( const char *s, const char *key ) {
line 1857
;1844:
;1845:	char	pkey[BIG_INFO_KEY];
;1846:
;1847:	static	char value[2][BIG_INFO_VALUE];	// use two buffers so compares
;1848:
;1849:											// work without stomping on each other
;1850:
;1851:	static	int	valueindex = 0;
;1852:
;1853:	char	*o;
;1854:
;1855:	
;1856:
;1857:	if ( !s || !key ) {
ADDRLP4 8196
CNSTU4 0
ASGNU4
ADDRFP4 0
INDIRP4
CVPU4 4
ADDRLP4 8196
INDIRU4
EQU4 $319
ADDRFP4 4
INDIRP4
CVPU4 4
ADDRLP4 8196
INDIRU4
NEU4 $317
LABELV $319
line 1859
;1858:
;1859:		return "";
ADDRGP4 $320
RETP4
ADDRGP4 $314
JUMPV
LABELV $317
line 1865
;1860:
;1861:	}
;1862:
;1863:
;1864:
;1865:	if ( strlen( s ) >= BIG_INFO_STRING ) {
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 8200
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 8200
INDIRI4
CNSTI4 8192
LTI4 $321
line 1867
;1866:
;1867:		Com_Error( ERR_DROP, "Info_ValueForKey: oversize infostring" );
CNSTI4 1
ARGI4
ADDRGP4 $323
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 1869
;1868:
;1869:	}
LABELV $321
line 1873
;1870:
;1871:
;1872:
;1873:	valueindex ^= 1;
ADDRLP4 8204
ADDRGP4 $316
ASGNP4
ADDRLP4 8204
INDIRP4
ADDRLP4 8204
INDIRP4
INDIRI4
CNSTI4 1
BXORI4
ASGNI4
line 1875
;1874:
;1875:	if (*s == '\\')
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 92
NEI4 $327
line 1877
;1876:
;1877:		s++;
ADDRFP4 0
ADDRFP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRGP4 $327
JUMPV
LABELV $326
line 1881
;1878:
;1879:	while (1)
;1880:
;1881:	{
line 1883
;1882:
;1883:		o = pkey;
ADDRLP4 0
ADDRLP4 4
ASGNP4
ADDRGP4 $330
JUMPV
LABELV $329
line 1887
;1884:
;1885:		while (*s != '\\')
;1886:
;1887:		{
line 1889
;1888:
;1889:			if (!*s)
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $332
line 1891
;1890:
;1891:				return "";
ADDRGP4 $320
RETP4
ADDRGP4 $314
JUMPV
LABELV $332
line 1893
;1892:
;1893:			*o++ = *s++;
ADDRLP4 8208
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 8216
CNSTI4 1
ASGNI4
ADDRLP4 0
ADDRLP4 8208
INDIRP4
ADDRLP4 8216
INDIRI4
ADDP4
ASGNP4
ADDRLP4 8212
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
ADDRLP4 8212
INDIRP4
ADDRLP4 8216
INDIRI4
ADDP4
ASGNP4
ADDRLP4 8208
INDIRP4
ADDRLP4 8212
INDIRP4
INDIRI1
ASGNI1
line 1895
;1894:
;1895:		}
LABELV $330
line 1885
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 92
NEI4 $329
line 1897
;1896:
;1897:		*o = 0;
ADDRLP4 0
INDIRP4
CNSTI1 0
ASGNI1
line 1899
;1898:
;1899:		s++;
ADDRFP4 0
ADDRFP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 1903
;1900:
;1901:
;1902:
;1903:		o = value[valueindex];
ADDRLP4 0
ADDRGP4 $316
INDIRI4
CNSTI4 13
LSHI4
ADDRGP4 $315
ADDP4
ASGNP4
ADDRGP4 $335
JUMPV
LABELV $334
line 1909
;1904:
;1905:
;1906:
;1907:		while (*s != '\\' && *s)
;1908:
;1909:		{
line 1911
;1910:
;1911:			*o++ = *s++;
ADDRLP4 8208
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 8216
CNSTI4 1
ASGNI4
ADDRLP4 0
ADDRLP4 8208
INDIRP4
ADDRLP4 8216
INDIRI4
ADDP4
ASGNP4
ADDRLP4 8212
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
ADDRLP4 8212
INDIRP4
ADDRLP4 8216
INDIRI4
ADDP4
ASGNP4
ADDRLP4 8208
INDIRP4
ADDRLP4 8212
INDIRP4
INDIRI1
ASGNI1
line 1913
;1912:
;1913:		}
LABELV $335
line 1907
ADDRLP4 8208
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 8208
INDIRI4
CNSTI4 92
EQI4 $337
ADDRLP4 8208
INDIRI4
CNSTI4 0
NEI4 $334
LABELV $337
line 1915
;1914:
;1915:		*o = 0;
ADDRLP4 0
INDIRP4
CNSTI1 0
ASGNI1
line 1919
;1916:
;1917:
;1918:
;1919:		if (!Q_stricmp (key, pkey) )
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 4
ARGP4
ADDRLP4 8212
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 8212
INDIRI4
CNSTI4 0
NEI4 $338
line 1921
;1920:
;1921:			return value[valueindex];
ADDRGP4 $316
INDIRI4
CNSTI4 13
LSHI4
ADDRGP4 $315
ADDP4
RETP4
ADDRGP4 $314
JUMPV
LABELV $338
line 1925
;1922:
;1923:
;1924:
;1925:		if (!*s)
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $340
line 1927
;1926:
;1927:			break;
ADDRGP4 $328
JUMPV
LABELV $340
line 1929
;1928:
;1929:		s++;
ADDRFP4 0
ADDRFP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 1931
;1930:
;1931:	}
LABELV $327
line 1879
ADDRGP4 $326
JUMPV
LABELV $328
line 1935
;1932:
;1933:
;1934:
;1935:	return "";
ADDRGP4 $320
RETP4
LABELV $314
endproc Info_ValueForKey 8220 8
export Info_NextPair
proc Info_NextPair 20 0
line 1957
;1936:
;1937:}
;1938:
;1939:
;1940:
;1941:
;1942:
;1943:/*
;1944:
;1945:===================
;1946:
;1947:Info_NextPair
;1948:
;1949:
;1950:
;1951:Used to itterate through all the key/value pairs in an info string
;1952:
;1953:===================
;1954:
;1955:*/
;1956:
;1957:void Info_NextPair( const char **head, char *key, char *value ) {
line 1965
;1958:
;1959:	char	*o;
;1960:
;1961:	const char	*s;
;1962:
;1963:
;1964:
;1965:	s = *head;
ADDRLP4 0
ADDRFP4 0
INDIRP4
INDIRP4
ASGNP4
line 1969
;1966:
;1967:
;1968:
;1969:	if ( *s == '\\' ) {
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 92
NEI4 $343
line 1971
;1970:
;1971:		s++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 1973
;1972:
;1973:	}
LABELV $343
line 1975
;1974:
;1975:	key[0] = 0;
ADDRFP4 4
INDIRP4
CNSTI1 0
ASGNI1
line 1977
;1976:
;1977:	value[0] = 0;
ADDRFP4 8
INDIRP4
CNSTI1 0
ASGNI1
line 1981
;1978:
;1979:
;1980:
;1981:	o = key;
ADDRLP4 4
ADDRFP4 4
INDIRP4
ASGNP4
ADDRGP4 $346
JUMPV
LABELV $345
line 1983
;1982:
;1983:	while ( *s != '\\' ) {
line 1985
;1984:
;1985:		if ( !*s ) {
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $348
line 1987
;1986:
;1987:			*o = 0;
ADDRLP4 4
INDIRP4
CNSTI1 0
ASGNI1
line 1989
;1988:
;1989:			*head = s;
ADDRFP4 0
INDIRP4
ADDRLP4 0
INDIRP4
ASGNP4
line 1991
;1990:
;1991:			return;
ADDRGP4 $342
JUMPV
LABELV $348
line 1995
;1992:
;1993:		}
;1994:
;1995:		*o++ = *s++;
ADDRLP4 8
ADDRLP4 4
INDIRP4
ASGNP4
ADDRLP4 16
CNSTI4 1
ASGNI4
ADDRLP4 4
ADDRLP4 8
INDIRP4
ADDRLP4 16
INDIRI4
ADDP4
ASGNP4
ADDRLP4 12
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 0
ADDRLP4 12
INDIRP4
ADDRLP4 16
INDIRI4
ADDP4
ASGNP4
ADDRLP4 8
INDIRP4
ADDRLP4 12
INDIRP4
INDIRI1
ASGNI1
line 1997
;1996:
;1997:	}
LABELV $346
line 1983
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 92
NEI4 $345
line 1999
;1998:
;1999:	*o = 0;
ADDRLP4 4
INDIRP4
CNSTI1 0
ASGNI1
line 2001
;2000:
;2001:	s++;
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 2005
;2002:
;2003:
;2004:
;2005:	o = value;
ADDRLP4 4
ADDRFP4 8
INDIRP4
ASGNP4
ADDRGP4 $351
JUMPV
LABELV $350
line 2007
;2006:
;2007:	while ( *s != '\\' && *s ) {
line 2009
;2008:
;2009:		*o++ = *s++;
ADDRLP4 8
ADDRLP4 4
INDIRP4
ASGNP4
ADDRLP4 16
CNSTI4 1
ASGNI4
ADDRLP4 4
ADDRLP4 8
INDIRP4
ADDRLP4 16
INDIRI4
ADDP4
ASGNP4
ADDRLP4 12
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 0
ADDRLP4 12
INDIRP4
ADDRLP4 16
INDIRI4
ADDP4
ASGNP4
ADDRLP4 8
INDIRP4
ADDRLP4 12
INDIRP4
INDIRI1
ASGNI1
line 2011
;2010:
;2011:	}
LABELV $351
line 2007
ADDRLP4 8
ADDRLP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 8
INDIRI4
CNSTI4 92
EQI4 $353
ADDRLP4 8
INDIRI4
CNSTI4 0
NEI4 $350
LABELV $353
line 2013
;2012:
;2013:	*o = 0;
ADDRLP4 4
INDIRP4
CNSTI1 0
ASGNI1
line 2017
;2014:
;2015:
;2016:
;2017:	*head = s;
ADDRFP4 0
INDIRP4
ADDRLP4 0
INDIRP4
ASGNP4
line 2019
;2018:
;2019:}
LABELV $342
endproc Info_NextPair 20 0
export Info_RemoveKey
proc Info_RemoveKey 2076 8
line 2035
;2020:
;2021:
;2022:
;2023:
;2024:
;2025:/*
;2026:
;2027:===================
;2028:
;2029:Info_RemoveKey
;2030:
;2031:===================
;2032:
;2033:*/
;2034:
;2035:void Info_RemoveKey( char *s, const char *key ) {
line 2047
;2036:
;2037:	char	*start;
;2038:
;2039:	char	pkey[MAX_INFO_KEY];
;2040:
;2041:	char	value[MAX_INFO_VALUE];
;2042:
;2043:	char	*o;
;2044:
;2045:
;2046:
;2047:	if ( strlen( s ) >= MAX_INFO_STRING ) {
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 2056
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 2056
INDIRI4
CNSTI4 1024
LTI4 $355
line 2049
;2048:
;2049:		Com_Error( ERR_DROP, "Info_RemoveKey: oversize infostring" );
CNSTI4 1
ARGI4
ADDRGP4 $357
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 2051
;2050:
;2051:	}
LABELV $355
line 2055
;2052:
;2053:
;2054:
;2055:	if (strchr (key, '\\')) {
ADDRFP4 4
INDIRP4
ARGP4
CNSTI4 92
ARGI4
ADDRLP4 2060
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 2060
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $361
line 2057
;2056:
;2057:		return;
ADDRGP4 $354
JUMPV
LABELV $360
line 2065
;2058:
;2059:	}
;2060:
;2061:
;2062:
;2063:	while (1)
;2064:
;2065:	{
line 2067
;2066:
;2067:		start = s;
ADDRLP4 1028
ADDRFP4 0
INDIRP4
ASGNP4
line 2069
;2068:
;2069:		if (*s == '\\')
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 92
NEI4 $363
line 2071
;2070:
;2071:			s++;
ADDRFP4 0
ADDRFP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
LABELV $363
line 2073
;2072:
;2073:		o = pkey;
ADDRLP4 0
ADDRLP4 4
ASGNP4
ADDRGP4 $366
JUMPV
LABELV $365
line 2077
;2074:
;2075:		while (*s != '\\')
;2076:
;2077:		{
line 2079
;2078:
;2079:			if (!*s)
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $368
line 2081
;2080:
;2081:				return;
ADDRGP4 $354
JUMPV
LABELV $368
line 2083
;2082:
;2083:			*o++ = *s++;
ADDRLP4 2064
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 2072
CNSTI4 1
ASGNI4
ADDRLP4 0
ADDRLP4 2064
INDIRP4
ADDRLP4 2072
INDIRI4
ADDP4
ASGNP4
ADDRLP4 2068
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
ADDRLP4 2068
INDIRP4
ADDRLP4 2072
INDIRI4
ADDP4
ASGNP4
ADDRLP4 2064
INDIRP4
ADDRLP4 2068
INDIRP4
INDIRI1
ASGNI1
line 2085
;2084:
;2085:		}
LABELV $366
line 2075
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 92
NEI4 $365
line 2087
;2086:
;2087:		*o = 0;
ADDRLP4 0
INDIRP4
CNSTI1 0
ASGNI1
line 2089
;2088:
;2089:		s++;
ADDRFP4 0
ADDRFP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 2093
;2090:
;2091:
;2092:
;2093:		o = value;
ADDRLP4 0
ADDRLP4 1032
ASGNP4
ADDRGP4 $371
JUMPV
LABELV $370
line 2097
;2094:
;2095:		while (*s != '\\' && *s)
;2096:
;2097:		{
line 2099
;2098:
;2099:			if (!*s)
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $373
line 2101
;2100:
;2101:				return;
ADDRGP4 $354
JUMPV
LABELV $373
line 2103
;2102:
;2103:			*o++ = *s++;
ADDRLP4 2064
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 2072
CNSTI4 1
ASGNI4
ADDRLP4 0
ADDRLP4 2064
INDIRP4
ADDRLP4 2072
INDIRI4
ADDP4
ASGNP4
ADDRLP4 2068
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
ADDRLP4 2068
INDIRP4
ADDRLP4 2072
INDIRI4
ADDP4
ASGNP4
ADDRLP4 2064
INDIRP4
ADDRLP4 2068
INDIRP4
INDIRI1
ASGNI1
line 2105
;2104:
;2105:		}
LABELV $371
line 2095
ADDRLP4 2064
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 2064
INDIRI4
CNSTI4 92
EQI4 $375
ADDRLP4 2064
INDIRI4
CNSTI4 0
NEI4 $370
LABELV $375
line 2107
;2106:
;2107:		*o = 0;
ADDRLP4 0
INDIRP4
CNSTI1 0
ASGNI1
line 2111
;2108:
;2109:
;2110:
;2111:		if (!strcmp (key, pkey) )
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 4
ARGP4
ADDRLP4 2068
ADDRGP4 strcmp
CALLI4
ASGNI4
ADDRLP4 2068
INDIRI4
CNSTI4 0
NEI4 $376
line 2113
;2112:
;2113:		{
line 2115
;2114:
;2115:			strcpy (start, s);	// remove this part
ADDRLP4 1028
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 strcpy
CALLP4
pop
line 2117
;2116:
;2117:			return;
ADDRGP4 $354
JUMPV
LABELV $376
line 2123
;2118:
;2119:		}
;2120:
;2121:
;2122:
;2123:		if (!*s)
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $378
line 2125
;2124:
;2125:			return;
ADDRGP4 $354
JUMPV
LABELV $378
line 2127
;2126:
;2127:	}
LABELV $361
line 2063
ADDRGP4 $360
JUMPV
line 2131
;2128:
;2129:
;2130:
;2131:}
LABELV $354
endproc Info_RemoveKey 2076 8
export Info_RemoveKey_Big
proc Info_RemoveKey_Big 16412 8
line 2145
;2132:
;2133:
;2134:
;2135:/*
;2136:
;2137:===================
;2138:
;2139:Info_RemoveKey_Big
;2140:
;2141:===================
;2142:
;2143:*/
;2144:
;2145:void Info_RemoveKey_Big( char *s, const char *key ) {
line 2157
;2146:
;2147:	char	*start;
;2148:
;2149:	char	pkey[BIG_INFO_KEY];
;2150:
;2151:	char	value[BIG_INFO_VALUE];
;2152:
;2153:	char	*o;
;2154:
;2155:
;2156:
;2157:	if ( strlen( s ) >= BIG_INFO_STRING ) {
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 16392
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 16392
INDIRI4
CNSTI4 8192
LTI4 $381
line 2159
;2158:
;2159:		Com_Error( ERR_DROP, "Info_RemoveKey_Big: oversize infostring" );
CNSTI4 1
ARGI4
ADDRGP4 $383
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 2161
;2160:
;2161:	}
LABELV $381
line 2165
;2162:
;2163:
;2164:
;2165:	if (strchr (key, '\\')) {
ADDRFP4 4
INDIRP4
ARGP4
CNSTI4 92
ARGI4
ADDRLP4 16396
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 16396
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $387
line 2167
;2166:
;2167:		return;
ADDRGP4 $380
JUMPV
LABELV $386
line 2175
;2168:
;2169:	}
;2170:
;2171:
;2172:
;2173:	while (1)
;2174:
;2175:	{
line 2177
;2176:
;2177:		start = s;
ADDRLP4 8196
ADDRFP4 0
INDIRP4
ASGNP4
line 2179
;2178:
;2179:		if (*s == '\\')
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 92
NEI4 $389
line 2181
;2180:
;2181:			s++;
ADDRFP4 0
ADDRFP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
LABELV $389
line 2183
;2182:
;2183:		o = pkey;
ADDRLP4 0
ADDRLP4 4
ASGNP4
ADDRGP4 $392
JUMPV
LABELV $391
line 2187
;2184:
;2185:		while (*s != '\\')
;2186:
;2187:		{
line 2189
;2188:
;2189:			if (!*s)
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $394
line 2191
;2190:
;2191:				return;
ADDRGP4 $380
JUMPV
LABELV $394
line 2193
;2192:
;2193:			*o++ = *s++;
ADDRLP4 16400
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 16408
CNSTI4 1
ASGNI4
ADDRLP4 0
ADDRLP4 16400
INDIRP4
ADDRLP4 16408
INDIRI4
ADDP4
ASGNP4
ADDRLP4 16404
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
ADDRLP4 16404
INDIRP4
ADDRLP4 16408
INDIRI4
ADDP4
ASGNP4
ADDRLP4 16400
INDIRP4
ADDRLP4 16404
INDIRP4
INDIRI1
ASGNI1
line 2195
;2194:
;2195:		}
LABELV $392
line 2185
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 92
NEI4 $391
line 2197
;2196:
;2197:		*o = 0;
ADDRLP4 0
INDIRP4
CNSTI1 0
ASGNI1
line 2199
;2198:
;2199:		s++;
ADDRFP4 0
ADDRFP4 0
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
line 2203
;2200:
;2201:
;2202:
;2203:		o = value;
ADDRLP4 0
ADDRLP4 8200
ASGNP4
ADDRGP4 $397
JUMPV
LABELV $396
line 2207
;2204:
;2205:		while (*s != '\\' && *s)
;2206:
;2207:		{
line 2209
;2208:
;2209:			if (!*s)
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $399
line 2211
;2210:
;2211:				return;
ADDRGP4 $380
JUMPV
LABELV $399
line 2213
;2212:
;2213:			*o++ = *s++;
ADDRLP4 16400
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 16408
CNSTI4 1
ASGNI4
ADDRLP4 0
ADDRLP4 16400
INDIRP4
ADDRLP4 16408
INDIRI4
ADDP4
ASGNP4
ADDRLP4 16404
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
ADDRLP4 16404
INDIRP4
ADDRLP4 16408
INDIRI4
ADDP4
ASGNP4
ADDRLP4 16400
INDIRP4
ADDRLP4 16404
INDIRP4
INDIRI1
ASGNI1
line 2215
;2214:
;2215:		}
LABELV $397
line 2205
ADDRLP4 16400
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
ASGNI4
ADDRLP4 16400
INDIRI4
CNSTI4 92
EQI4 $401
ADDRLP4 16400
INDIRI4
CNSTI4 0
NEI4 $396
LABELV $401
line 2217
;2216:
;2217:		*o = 0;
ADDRLP4 0
INDIRP4
CNSTI1 0
ASGNI1
line 2221
;2218:
;2219:
;2220:
;2221:		if (!strcmp (key, pkey) )
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 4
ARGP4
ADDRLP4 16404
ADDRGP4 strcmp
CALLI4
ASGNI4
ADDRLP4 16404
INDIRI4
CNSTI4 0
NEI4 $402
line 2223
;2222:
;2223:		{
line 2225
;2224:
;2225:			strcpy (start, s);	// remove this part
ADDRLP4 8196
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 strcpy
CALLP4
pop
line 2227
;2226:
;2227:			return;
ADDRGP4 $380
JUMPV
LABELV $402
line 2233
;2228:
;2229:		}
;2230:
;2231:
;2232:
;2233:		if (!*s)
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
CNSTI4 0
NEI4 $404
line 2235
;2234:
;2235:			return;
ADDRGP4 $380
JUMPV
LABELV $404
line 2237
;2236:
;2237:	}
LABELV $387
line 2173
ADDRGP4 $386
JUMPV
line 2241
;2238:
;2239:
;2240:
;2241:}
LABELV $380
endproc Info_RemoveKey_Big 16412 8
export Info_Validate
proc Info_Validate 8 8
line 2267
;2242:
;2243:
;2244:
;2245:
;2246:
;2247:
;2248:
;2249:
;2250:
;2251:/*
;2252:
;2253:==================
;2254:
;2255:Info_Validate
;2256:
;2257:
;2258:
;2259:Some characters are illegal in info strings because they
;2260:
;2261:can mess up the server's parsing
;2262:
;2263:==================
;2264:
;2265:*/
;2266:
;2267:qboolean Info_Validate( const char *s ) {
line 2269
;2268:
;2269:	if ( strchr( s, '\"' ) ) {
ADDRFP4 0
INDIRP4
ARGP4
CNSTI4 34
ARGI4
ADDRLP4 0
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $407
line 2271
;2270:
;2271:		return qfalse;
CNSTI4 0
RETI4
ADDRGP4 $406
JUMPV
LABELV $407
line 2275
;2272:
;2273:	}
;2274:
;2275:	if ( strchr( s, ';' ) ) {
ADDRFP4 0
INDIRP4
ARGP4
CNSTI4 59
ARGI4
ADDRLP4 4
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 4
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $409
line 2277
;2276:
;2277:		return qfalse;
CNSTI4 0
RETI4
ADDRGP4 $406
JUMPV
LABELV $409
line 2281
;2278:
;2279:	}
;2280:
;2281:	return qtrue;
CNSTI4 1
RETI4
LABELV $406
endproc Info_Validate 8 8
export Info_SetValueForKey
proc Info_SetValueForKey 1068 20
line 2301
;2282:
;2283:}
;2284:
;2285:
;2286:
;2287:/*
;2288:
;2289:==================
;2290:
;2291:Info_SetValueForKey
;2292:
;2293:
;2294:
;2295:Changes or adds a key/value pair
;2296:
;2297:==================
;2298:
;2299:*/
;2300:
;2301:void Info_SetValueForKey( char *s, const char *key, const char *value ) {
line 2307
;2302:
;2303:	char	newi[MAX_INFO_STRING];
;2304:
;2305:
;2306:
;2307:	if ( strlen( s ) >= MAX_INFO_STRING ) {
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 1024
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 1024
INDIRI4
CNSTI4 1024
LTI4 $412
line 2309
;2308:
;2309:		Com_Error( ERR_DROP, "Info_SetValueForKey: oversize infostring" );
CNSTI4 1
ARGI4
ADDRGP4 $414
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 2311
;2310:
;2311:	}
LABELV $412
line 2315
;2312:
;2313:
;2314:
;2315:	if (strchr (key, '\\') || strchr (value, '\\'))
ADDRFP4 4
INDIRP4
ARGP4
CNSTI4 92
ARGI4
ADDRLP4 1028
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 1028
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $417
ADDRFP4 8
INDIRP4
ARGP4
CNSTI4 92
ARGI4
ADDRLP4 1032
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 1032
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $415
LABELV $417
line 2317
;2316:
;2317:	{
line 2319
;2318:
;2319:		Com_Printf ("Can't use keys or values with a \\\n");
ADDRGP4 $418
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
line 2321
;2320:
;2321:		return;
ADDRGP4 $411
JUMPV
LABELV $415
line 2327
;2322:
;2323:	}
;2324:
;2325:
;2326:
;2327:	if (strchr (key, ';') || strchr (value, ';'))
ADDRFP4 4
INDIRP4
ARGP4
CNSTI4 59
ARGI4
ADDRLP4 1036
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 1036
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $421
ADDRFP4 8
INDIRP4
ARGP4
CNSTI4 59
ARGI4
ADDRLP4 1040
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 1040
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $419
LABELV $421
line 2329
;2328:
;2329:	{
line 2331
;2330:
;2331:		Com_Printf ("Can't use keys or values with a semicolon\n");
ADDRGP4 $422
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
line 2333
;2332:
;2333:		return;
ADDRGP4 $411
JUMPV
LABELV $419
line 2339
;2334:
;2335:	}
;2336:
;2337:
;2338:
;2339:	if (strchr (key, '\"') || strchr (value, '\"'))
ADDRFP4 4
INDIRP4
ARGP4
CNSTI4 34
ARGI4
ADDRLP4 1044
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 1044
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $425
ADDRFP4 8
INDIRP4
ARGP4
CNSTI4 34
ARGI4
ADDRLP4 1048
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 1048
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $423
LABELV $425
line 2341
;2340:
;2341:	{
line 2343
;2342:
;2343:		Com_Printf ("Can't use keys or values with a \"\n");
ADDRGP4 $426
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
line 2345
;2344:
;2345:		return;
ADDRGP4 $411
JUMPV
LABELV $423
line 2351
;2346:
;2347:	}
;2348:
;2349:
;2350:
;2351:	Info_RemoveKey (s, key);
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRGP4 Info_RemoveKey
CALLV
pop
line 2353
;2352:
;2353:	if (!value || !strlen(value))
ADDRLP4 1052
ADDRFP4 8
INDIRP4
ASGNP4
ADDRLP4 1052
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $429
ADDRLP4 1052
INDIRP4
ARGP4
ADDRLP4 1056
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 1056
INDIRI4
CNSTI4 0
NEI4 $427
LABELV $429
line 2355
;2354:
;2355:		return;
ADDRGP4 $411
JUMPV
LABELV $427
line 2359
;2356:
;2357:
;2358:
;2359:	Com_sprintf (newi, sizeof(newi), "\\%s\\%s", key, value);
ADDRLP4 0
ARGP4
CNSTI4 1024
ARGI4
ADDRGP4 $430
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRFP4 8
INDIRP4
ARGP4
ADDRGP4 Com_sprintf
CALLV
pop
line 2363
;2360:
;2361:
;2362:
;2363:	if (strlen(newi) + strlen(s) > MAX_INFO_STRING)
ADDRLP4 0
ARGP4
ADDRLP4 1060
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 1064
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 1060
INDIRI4
ADDRLP4 1064
INDIRI4
ADDI4
CNSTI4 1024
LEI4 $431
line 2365
;2364:
;2365:	{
line 2367
;2366:
;2367:		Com_Printf ("Info string length exceeded\n");
ADDRGP4 $433
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
line 2369
;2368:
;2369:		return;
ADDRGP4 $411
JUMPV
LABELV $431
line 2375
;2370:
;2371:	}
;2372:
;2373:
;2374:
;2375:	strcat (newi, s);
ADDRLP4 0
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 strcat
CALLP4
pop
line 2377
;2376:
;2377:	strcpy (s, newi);
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 strcpy
CALLP4
pop
line 2379
;2378:
;2379:}
LABELV $411
endproc Info_SetValueForKey 1068 20
export Info_SetValueForKey_Big
proc Info_SetValueForKey_Big 8236 20
line 2397
;2380:
;2381:
;2382:
;2383:/*
;2384:
;2385:==================
;2386:
;2387:Info_SetValueForKey_Big
;2388:
;2389:
;2390:
;2391:Changes or adds a key/value pair
;2392:
;2393:==================
;2394:
;2395:*/
;2396:
;2397:void Info_SetValueForKey_Big( char *s, const char *key, const char *value ) {
line 2403
;2398:
;2399:	char	newi[BIG_INFO_STRING];
;2400:
;2401:
;2402:
;2403:	if ( strlen( s ) >= BIG_INFO_STRING ) {
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 8192
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 8192
INDIRI4
CNSTI4 8192
LTI4 $435
line 2405
;2404:
;2405:		Com_Error( ERR_DROP, "Info_SetValueForKey: oversize infostring" );
CNSTI4 1
ARGI4
ADDRGP4 $414
ARGP4
ADDRGP4 Com_Error
CALLV
pop
line 2407
;2406:
;2407:	}
LABELV $435
line 2411
;2408:
;2409:
;2410:
;2411:	if (strchr (key, '\\') || strchr (value, '\\'))
ADDRFP4 4
INDIRP4
ARGP4
CNSTI4 92
ARGI4
ADDRLP4 8196
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 8196
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $439
ADDRFP4 8
INDIRP4
ARGP4
CNSTI4 92
ARGI4
ADDRLP4 8200
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 8200
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $437
LABELV $439
line 2413
;2412:
;2413:	{
line 2415
;2414:
;2415:		Com_Printf ("Can't use keys or values with a \\\n");
ADDRGP4 $418
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
line 2417
;2416:
;2417:		return;
ADDRGP4 $434
JUMPV
LABELV $437
line 2423
;2418:
;2419:	}
;2420:
;2421:
;2422:
;2423:	if (strchr (key, ';') || strchr (value, ';'))
ADDRFP4 4
INDIRP4
ARGP4
CNSTI4 59
ARGI4
ADDRLP4 8204
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 8204
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $442
ADDRFP4 8
INDIRP4
ARGP4
CNSTI4 59
ARGI4
ADDRLP4 8208
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 8208
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $440
LABELV $442
line 2425
;2424:
;2425:	{
line 2427
;2426:
;2427:		Com_Printf ("Can't use keys or values with a semicolon\n");
ADDRGP4 $422
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
line 2429
;2428:
;2429:		return;
ADDRGP4 $434
JUMPV
LABELV $440
line 2435
;2430:
;2431:	}
;2432:
;2433:
;2434:
;2435:	if (strchr (key, '\"') || strchr (value, '\"'))
ADDRFP4 4
INDIRP4
ARGP4
CNSTI4 34
ARGI4
ADDRLP4 8212
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 8212
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $445
ADDRFP4 8
INDIRP4
ARGP4
CNSTI4 34
ARGI4
ADDRLP4 8216
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 8216
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $443
LABELV $445
line 2437
;2436:
;2437:	{
line 2439
;2438:
;2439:		Com_Printf ("Can't use keys or values with a \"\n");
ADDRGP4 $426
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
line 2441
;2440:
;2441:		return;
ADDRGP4 $434
JUMPV
LABELV $443
line 2447
;2442:
;2443:	}
;2444:
;2445:
;2446:
;2447:	Info_RemoveKey_Big (s, key);
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRGP4 Info_RemoveKey_Big
CALLV
pop
line 2449
;2448:
;2449:	if (!value || !strlen(value))
ADDRLP4 8220
ADDRFP4 8
INDIRP4
ASGNP4
ADDRLP4 8220
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $448
ADDRLP4 8220
INDIRP4
ARGP4
ADDRLP4 8224
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 8224
INDIRI4
CNSTI4 0
NEI4 $446
LABELV $448
line 2451
;2450:
;2451:		return;
ADDRGP4 $434
JUMPV
LABELV $446
line 2455
;2452:
;2453:
;2454:
;2455:	Com_sprintf (newi, sizeof(newi), "\\%s\\%s", key, value);
ADDRLP4 0
ARGP4
CNSTI4 8192
ARGI4
ADDRGP4 $430
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRFP4 8
INDIRP4
ARGP4
ADDRGP4 Com_sprintf
CALLV
pop
line 2459
;2456:
;2457:
;2458:
;2459:	if (strlen(newi) + strlen(s) > BIG_INFO_STRING)
ADDRLP4 0
ARGP4
ADDRLP4 8228
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 8232
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 8228
INDIRI4
ADDRLP4 8232
INDIRI4
ADDI4
CNSTI4 8192
LEI4 $449
line 2461
;2460:
;2461:	{
line 2463
;2462:
;2463:		Com_Printf ("BIG Info string length exceeded\n");
ADDRGP4 $451
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
line 2465
;2464:
;2465:		return;
ADDRGP4 $434
JUMPV
LABELV $449
line 2471
;2466:
;2467:	}
;2468:
;2469:
;2470:
;2471:	strcat (s, newi);
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 strcat
CALLP4
pop
line 2473
;2472:
;2473:}
LABELV $434
endproc Info_SetValueForKey_Big 8236 20
bss
align 4
LABELV com_lines
skip 4
align 1
LABELV com_parsename
skip 1024
align 1
LABELV com_token
skip 1024
import Com_Printf
import Com_Error
import Info_RemoveKey_big
import PerpendicularVector
import AngleVectors
import MatrixMultiply
import MakeNormalVectors
import RotateAroundDirection
import RotatePointAroundVector
import ProjectPointOnPlane
import PlaneFromPoints
import AngleDelta
import AngleNormalize180
import AngleNormalize360
import AnglesSubtract
import AngleSubtract
import LerpAngle
import AngleMod
import BoxOnPlaneSide
import SetPlaneSignbits
import AxisCopy
import AxisClear
import AnglesToAxis
import vectoangles
import Q_crandom
import Q_random
import Q_rand
import Q_acos
import Q_log2
import VectorRotate
import Vector4Scale
import VectorNormalize2
import VectorNormalize
import CrossProduct
import VectorInverse
import VectorNormalizeFast
import DistanceSquared
import Distance
import VectorLengthSquared
import VectorLength
import VectorCompare
import AddPointToBounds
import ClearBounds
import RadiusFromBounds
import NormalizeColor
import ColorBytes4
import ColorBytes3
import _VectorMA
import _VectorScale
import _VectorCopy
import _VectorAdd
import _VectorSubtract
import _DotProduct
import ByteToDir
import DirToByte
import ClampShort
import ClampChar
import Q_rsqrt
import Q_fabs
import axisDefault
import vec3_origin
import g_color_table
import colorDkGrey
import colorMdGrey
import colorLtGrey
import colorWhite
import colorCyan
import colorMagenta
import colorYellow
import colorBlue
import colorGreen
import colorRed
import colorBlack
import bytedirs
import Com_Memcpy
import Com_Memset
import Hunk_Alloc
import acos
import fabs
import abs
import tan
import atan2
import cos
import sin
import sqrt
import floor
import ceil
import memcpy
import memset
import memmove
import sscanf
import vsprintf
import _atoi
import atoi
import _atof
import atof
import toupper
import tolower
import strncpy
import strstr
import strchr
import strcmp
import strcpy
import strcat
import strlen
import rand
import srand
import qsort
lit
align 1
LABELV $451
byte 1 66
byte 1 73
byte 1 71
byte 1 32
byte 1 73
byte 1 110
byte 1 102
byte 1 111
byte 1 32
byte 1 115
byte 1 116
byte 1 114
byte 1 105
byte 1 110
byte 1 103
byte 1 32
byte 1 108
byte 1 101
byte 1 110
byte 1 103
byte 1 116
byte 1 104
byte 1 32
byte 1 101
byte 1 120
byte 1 99
byte 1 101
byte 1 101
byte 1 100
byte 1 101
byte 1 100
byte 1 10
byte 1 0
align 1
LABELV $433
byte 1 73
byte 1 110
byte 1 102
byte 1 111
byte 1 32
byte 1 115
byte 1 116
byte 1 114
byte 1 105
byte 1 110
byte 1 103
byte 1 32
byte 1 108
byte 1 101
byte 1 110
byte 1 103
byte 1 116
byte 1 104
byte 1 32
byte 1 101
byte 1 120
byte 1 99
byte 1 101
byte 1 101
byte 1 100
byte 1 101
byte 1 100
byte 1 10
byte 1 0
align 1
LABELV $430
byte 1 92
byte 1 37
byte 1 115
byte 1 92
byte 1 37
byte 1 115
byte 1 0
align 1
LABELV $426
byte 1 67
byte 1 97
byte 1 110
byte 1 39
byte 1 116
byte 1 32
byte 1 117
byte 1 115
byte 1 101
byte 1 32
byte 1 107
byte 1 101
byte 1 121
byte 1 115
byte 1 32
byte 1 111
byte 1 114
byte 1 32
byte 1 118
byte 1 97
byte 1 108
byte 1 117
byte 1 101
byte 1 115
byte 1 32
byte 1 119
byte 1 105
byte 1 116
byte 1 104
byte 1 32
byte 1 97
byte 1 32
byte 1 34
byte 1 10
byte 1 0
align 1
LABELV $422
byte 1 67
byte 1 97
byte 1 110
byte 1 39
byte 1 116
byte 1 32
byte 1 117
byte 1 115
byte 1 101
byte 1 32
byte 1 107
byte 1 101
byte 1 121
byte 1 115
byte 1 32
byte 1 111
byte 1 114
byte 1 32
byte 1 118
byte 1 97
byte 1 108
byte 1 117
byte 1 101
byte 1 115
byte 1 32
byte 1 119
byte 1 105
byte 1 116
byte 1 104
byte 1 32
byte 1 97
byte 1 32
byte 1 115
byte 1 101
byte 1 109
byte 1 105
byte 1 99
byte 1 111
byte 1 108
byte 1 111
byte 1 110
byte 1 10
byte 1 0
align 1
LABELV $418
byte 1 67
byte 1 97
byte 1 110
byte 1 39
byte 1 116
byte 1 32
byte 1 117
byte 1 115
byte 1 101
byte 1 32
byte 1 107
byte 1 101
byte 1 121
byte 1 115
byte 1 32
byte 1 111
byte 1 114
byte 1 32
byte 1 118
byte 1 97
byte 1 108
byte 1 117
byte 1 101
byte 1 115
byte 1 32
byte 1 119
byte 1 105
byte 1 116
byte 1 104
byte 1 32
byte 1 97
byte 1 32
byte 1 92
byte 1 10
byte 1 0
align 1
LABELV $414
byte 1 73
byte 1 110
byte 1 102
byte 1 111
byte 1 95
byte 1 83
byte 1 101
byte 1 116
byte 1 86
byte 1 97
byte 1 108
byte 1 117
byte 1 101
byte 1 70
byte 1 111
byte 1 114
byte 1 75
byte 1 101
byte 1 121
byte 1 58
byte 1 32
byte 1 111
byte 1 118
byte 1 101
byte 1 114
byte 1 115
byte 1 105
byte 1 122
byte 1 101
byte 1 32
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 115
byte 1 116
byte 1 114
byte 1 105
byte 1 110
byte 1 103
byte 1 0
align 1
LABELV $383
byte 1 73
byte 1 110
byte 1 102
byte 1 111
byte 1 95
byte 1 82
byte 1 101
byte 1 109
byte 1 111
byte 1 118
byte 1 101
byte 1 75
byte 1 101
byte 1 121
byte 1 95
byte 1 66
byte 1 105
byte 1 103
byte 1 58
byte 1 32
byte 1 111
byte 1 118
byte 1 101
byte 1 114
byte 1 115
byte 1 105
byte 1 122
byte 1 101
byte 1 32
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 115
byte 1 116
byte 1 114
byte 1 105
byte 1 110
byte 1 103
byte 1 0
align 1
LABELV $357
byte 1 73
byte 1 110
byte 1 102
byte 1 111
byte 1 95
byte 1 82
byte 1 101
byte 1 109
byte 1 111
byte 1 118
byte 1 101
byte 1 75
byte 1 101
byte 1 121
byte 1 58
byte 1 32
byte 1 111
byte 1 118
byte 1 101
byte 1 114
byte 1 115
byte 1 105
byte 1 122
byte 1 101
byte 1 32
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 115
byte 1 116
byte 1 114
byte 1 105
byte 1 110
byte 1 103
byte 1 0
align 1
LABELV $323
byte 1 73
byte 1 110
byte 1 102
byte 1 111
byte 1 95
byte 1 86
byte 1 97
byte 1 108
byte 1 117
byte 1 101
byte 1 70
byte 1 111
byte 1 114
byte 1 75
byte 1 101
byte 1 121
byte 1 58
byte 1 32
byte 1 111
byte 1 118
byte 1 101
byte 1 114
byte 1 115
byte 1 105
byte 1 122
byte 1 101
byte 1 32
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 115
byte 1 116
byte 1 114
byte 1 105
byte 1 110
byte 1 103
byte 1 0
align 1
LABELV $320
byte 1 0
align 1
LABELV $309
byte 1 67
byte 1 111
byte 1 109
byte 1 95
byte 1 115
byte 1 112
byte 1 114
byte 1 105
byte 1 110
byte 1 116
byte 1 102
byte 1 58
byte 1 32
byte 1 111
byte 1 118
byte 1 101
byte 1 114
byte 1 102
byte 1 108
byte 1 111
byte 1 119
byte 1 32
byte 1 111
byte 1 102
byte 1 32
byte 1 37
byte 1 105
byte 1 32
byte 1 105
byte 1 110
byte 1 32
byte 1 37
byte 1 105
byte 1 10
byte 1 0
align 1
LABELV $306
byte 1 67
byte 1 111
byte 1 109
byte 1 95
byte 1 115
byte 1 112
byte 1 114
byte 1 105
byte 1 110
byte 1 116
byte 1 102
byte 1 58
byte 1 32
byte 1 111
byte 1 118
byte 1 101
byte 1 114
byte 1 102
byte 1 108
byte 1 111
byte 1 119
byte 1 101
byte 1 100
byte 1 32
byte 1 98
byte 1 105
byte 1 103
byte 1 98
byte 1 117
byte 1 102
byte 1 102
byte 1 101
byte 1 114
byte 1 0
align 1
LABELV $285
byte 1 81
byte 1 95
byte 1 115
byte 1 116
byte 1 114
byte 1 99
byte 1 97
byte 1 116
byte 1 58
byte 1 32
byte 1 97
byte 1 108
byte 1 114
byte 1 101
byte 1 97
byte 1 100
byte 1 121
byte 1 32
byte 1 111
byte 1 118
byte 1 101
byte 1 114
byte 1 102
byte 1 108
byte 1 111
byte 1 119
byte 1 101
byte 1 100
byte 1 0
align 1
LABELV $235
byte 1 81
byte 1 95
byte 1 115
byte 1 116
byte 1 114
byte 1 110
byte 1 99
byte 1 112
byte 1 121
byte 1 122
byte 1 58
byte 1 32
byte 1 100
byte 1 101
byte 1 115
byte 1 116
byte 1 115
byte 1 105
byte 1 122
byte 1 101
byte 1 32
byte 1 60
byte 1 32
byte 1 49
byte 1 0
align 1
LABELV $232
byte 1 81
byte 1 95
byte 1 115
byte 1 116
byte 1 114
byte 1 110
byte 1 99
byte 1 112
byte 1 121
byte 1 122
byte 1 58
byte 1 32
byte 1 78
byte 1 85
byte 1 76
byte 1 76
byte 1 32
byte 1 115
byte 1 114
byte 1 99
byte 1 0
align 1
LABELV $229
byte 1 81
byte 1 95
byte 1 115
byte 1 116
byte 1 114
byte 1 110
byte 1 99
byte 1 112
byte 1 121
byte 1 122
byte 1 58
byte 1 32
byte 1 78
byte 1 85
byte 1 76
byte 1 76
byte 1 32
byte 1 100
byte 1 101
byte 1 115
byte 1 116
byte 1 0
align 1
LABELV $193
byte 1 41
byte 1 0
align 1
LABELV $188
byte 1 40
byte 1 0
align 1
LABELV $169
byte 1 77
byte 1 97
byte 1 116
byte 1 99
byte 1 104
byte 1 84
byte 1 111
byte 1 107
byte 1 101
byte 1 110
byte 1 58
byte 1 32
byte 1 37
byte 1 115
byte 1 32
byte 1 33
byte 1 61
byte 1 32
byte 1 37
byte 1 115
byte 1 0
align 1
LABELV $75
byte 1 87
byte 1 65
byte 1 82
byte 1 78
byte 1 73
byte 1 78
byte 1 71
byte 1 58
byte 1 32
byte 1 37
byte 1 115
byte 1 44
byte 1 32
byte 1 108
byte 1 105
byte 1 110
byte 1 101
byte 1 32
byte 1 37
byte 1 100
byte 1 58
byte 1 32
byte 1 37
byte 1 115
byte 1 10
byte 1 0
align 1
LABELV $71
byte 1 69
byte 1 82
byte 1 82
byte 1 79
byte 1 82
byte 1 58
byte 1 32
byte 1 37
byte 1 115
byte 1 44
byte 1 32
byte 1 108
byte 1 105
byte 1 110
byte 1 101
byte 1 32
byte 1 37
byte 1 100
byte 1 58
byte 1 32
byte 1 37
byte 1 115
byte 1 10
byte 1 0
align 1
LABELV $65
byte 1 37
byte 1 115
byte 1 0
align 1
LABELV $45
byte 1 37
byte 1 115
byte 1 37
byte 1 115
byte 1 0
