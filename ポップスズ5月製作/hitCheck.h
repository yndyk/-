//-----------------------------------------------------
// 
// 1:1‚Ì“–‚½‚è”»’èˆ—‚Ì’Ç‰Á
// 
// 
// 
//-----------------------------------------------------

#pragma once

// 1F•¡”‚Ì“–‚½‚è”»’è
bool HitCheckRectToRect(CHARACTER, int, CHARACTER*);
bool HitCheckRectToCircle(CHARACTER, int, CHARACTER*);
bool HitCheckCircleToCircle(CHARACTER, int, CHARACTER*);

// •¡”F•¡”‚Ì“–‚½‚è”»’è
bool HitCheckShotToEnemy(CHARACTER*, int, CHARACTER*, int);

// 1F1‚Ì“–‚½‚è”»’è
bool HitCheck(CHARACTER, CHARACTER);
