//-----------------------------------------------------
// 
// 1:1�̓����蔻�菈���̒ǉ�
// 
// 
// 
//-----------------------------------------------------

#pragma once

// 1�F�����̓����蔻��
bool HitCheckRectToRect(CHARACTER, int, CHARACTER*);
bool HitCheckRectToCircle(CHARACTER, int, CHARACTER*);
bool HitCheckCircleToCircle(CHARACTER, int, CHARACTER*);

// �����F�����̓����蔻��
bool HitCheckShotToEnemy(CHARACTER*, int, CHARACTER*, int);

// 1�F1�̓����蔻��
bool HitCheck(CHARACTER, CHARACTER);
