//-----------------------------------------------------
// 
// �e�֐���Square��Rect�ɕύX���܂���
// HitCheckCircleToCircle()�̏�����ǉ����܂���
// ������hitCheck.cpp�Ɉڍs���܂���
// 
//-----------------------------------------------------

#pragma once

// 1�F�����̓����蔻��
bool HitCheckRectToRect(CHARACTER, int, CHARACTER*);
bool HitCheckRectToCircle(CHARACTER, int, CHARACTER*);
bool HitCheckCircleToCircle(CHARACTER, int, CHARACTER*);
bool HitCheckShotToEnemy(CHARACTER*, int, CHARACTER*, int);
