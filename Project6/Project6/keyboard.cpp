#define _WIN32_WINNT 0x0600 // Windows Vista or later
#include <windows.h>
#include "keyboard.h"

void LEFT_AND_RIGHT_ARROWS_Key_Movement(player* player, DWORD64 currentTime, DWORD64 frameDelay) {
    int state_of_keybd_event = 0;
    static int isKeyHeldLeft = 0;
    static int isKeyHeldRight = 0;
    static DWORD64 lastPressTimeLeft = 0;
    static DWORD64 lastPressTimeRight = 0;
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        state_of_keybd_event = KEY_STATE_LEFT;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        state_of_keybd_event = KEY_STATE_RIGHT;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        state_of_keybd_event = KEY_STATE_LEFT_AND_RIGHT;
    }

    switch (state_of_keybd_event) {
    case KEY_STATE_LEFT:
        if (player->frame.ignoreKeys2) {
            break;
        }
        player->blue = 2;
        if (player->frame.ignoreKeys1) {
            break;
        }
        if (player->box.velocity.x > -X_MAX_SPEED)
            player->box.acceleration.x = -X_ACCELERATION;
        else {
            player->box.velocity.x = -X_MAX_SPEED;
            player->box.acceleration.x = 0;
        }
        if (!isKeyHeldLeft) {
            isKeyHeldLeft = 1;
            lastPressTimeLeft = currentTime;
        }
        if (currentTime - lastPressTimeLeft >= frameDelay) {
            player->frame.walkFrame = (player->frame.walkFrame + 1) % 4;
            lastPressTimeLeft = currentTime;
        }
        break;
    case KEY_STATE_RIGHT:
        if (player->frame.ignoreKeys2) {
            break;
        }
        player->blue = 1;
        if (player->frame.ignoreKeys1) {
            break;
        }
        if (player->box.velocity.x < X_MAX_SPEED)
            player->box.acceleration.x = X_ACCELERATION;
        else {
            player->box.velocity.x = X_MAX_SPEED;
            player->box.acceleration.x = 0;
        }
        if (!isKeyHeldRight) {
            isKeyHeldRight = 1;
            lastPressTimeRight = currentTime;
        }
        if (currentTime - lastPressTimeRight >= frameDelay) {
            player->frame.walkFrame = (player->frame.walkFrame + 1) % 4;
            lastPressTimeRight = currentTime;
        }
        break;
    case KEY_STATE_LEFT_AND_RIGHT:
        player->box.acceleration.x = 0;
        player->box.velocity.x = 0;
        isKeyHeldLeft = 0;
        isKeyHeldRight = 0;
        break;
    default:
        if (player->box.velocity.x < 0) {
            player->box.acceleration.x = X_ACCELERATION;
        }
        else if (player->box.velocity.x > 0) {
            player->box.acceleration.x = -X_ACCELERATION;
        }
        else {
            player->box.acceleration.x = 0;
        }
        isKeyHeldLeft = 0;
        isKeyHeldRight = 0;
        break;
    }
}

int Z_X_C_A_S_D_F_SPACE_CTRL_Key_Movements(player* player) {
    int state_of_keybd_event = 0;
    if (!player->frame.ignoreKeys1 && !player->frame.ignoreKeys2) {
        if (player->state == PLAYER_STATE_DEFAULT) {
            if (GetAsyncKeyState('Z') & 0x8000 && player->remaining_times_of_jump > 0) {
                player->box.velocity.y = JUMP_POWER;
                player->remaining_times_of_jump--;
                player->state = PLAYER_STATE_JUMP;
            }
        }
        DWORD64 currentTime = GetTickCount64();
        if (player->blue == 1) {
            if (GetAsyncKeyState('X') & 0x8000 && !player->frame.isAttacking) {
                player->frame.isAttacking = true;
                player->frame.attackFrame = 0;
            }
            else if (!player->frame.isAttacking) {
                player->frame.isAttacking = false;
            }
            if (GetAsyncKeyState('A') & 0x8000 && !player->frame.isAttackremoteing && player->state == PLAYER_STATE_DEFAULT) {
                player->frame.isAttackremoteing = true;
                player->frame.attackremoteFrame = 0;
                player->frame.ignoreKeys2 = true;
                player->box.velocity.x = 0;
                player->box.acceleration.x = 0;
                if (player->frame.isAttackremoteing) {
                    player->frame.isAttacking = false;
                    player->frame.isAttackuping = false;
                    player->frame.isDefensing = false;
                    player->frame.isDashing = false;
                    return 0;
                }
            }
            else if (!player->frame.isAttackremoteing) {
                player->frame.isAttackremoteing = false;
            }
            if (GetAsyncKeyState(VK_UP) & 0x8000 && !player->frame.isAttackuping) {
                player->frame.isAttackuping = true;
                player->frame.attackupFrame = 0;
            }
            else if (!player->frame.isAttackuping) {
                player->frame.isAttackuping = false;
            }
            if (GetAsyncKeyState('S') & 0x8000 && player->state == PLAYER_STATE_DEFAULT) {
                player->frame.isDefensing = true;
                player->frame.ignoreKeys1 = true;
                player->box.velocity.x = 0;
                player->box.acceleration.x = 0;
            }
            else {
                player->frame.isDefensing = false;
            }
            if (player->frame.isDefensing) {
                player->frame.isAttacking = false;
                player->frame.isAttackremoteing = false;
                player->frame.isAttackuping = false;
                player->frame.isDashing = false;
            }
            if (GetAsyncKeyState('C') & 0x8000 && !player->frame.isDashing) {
                player->frame.isDashing = true;
                player->frame.dashFrame = 0;
            }
        }
        else {
            if (GetAsyncKeyState('A') & 0x8000 && !player->frame.isAttackremoteing && player->state == PLAYER_STATE_DEFAULT) {
                player->frame.isAttackremoteing = true;
                player->frame.attackremoteFrame = 0;
                player->frame.ignoreKeys2 = true;
                player->box.velocity.x = 0;
                player->box.acceleration.x = 0;
                if (player->frame.isAttackremoteing) {
                    player->frame.isAttacking = false;
                    player->frame.isAttackuping = false;
                    player->frame.isDefensing = false;
                    player->frame.isDashing = false;
                    return 0;
                }
            }
            else if (!player->frame.isAttackremoteing) {
                player->frame.isAttackremoteing = false;
            }
            if (GetAsyncKeyState('X') & 0x8000 && !player->frame.isAttacking) {
                player->frame.isAttacking = true;
                player->frame.attackFrame = 0;
            }
            else if (!player->frame.isAttacking) {
                player->frame.isAttacking = false;
            }
            if (GetAsyncKeyState(VK_UP) & 0x8000 && !player->frame.isAttackuping) {
                player->frame.isAttackuping = true;
                player->frame.attackupFrame = 0;
            }
            else if (!player->frame.isAttackuping) {
                player->frame.isAttackuping = false;
            }
            if (GetAsyncKeyState('S') & 0x8000 && player->state == PLAYER_STATE_DEFAULT) {
                player->frame.isDefensing = true;
                player->frame.ignoreKeys1 = true;
                player->box.velocity.x = 0;
                player->box.acceleration.x = 0;
            }
            else {
                player->frame.isDefensing = false;
            }
            if (player->frame.isDefensing) {
                player->frame.isAttacking = false;
                player->frame.isAttackremoteing = false;
                player->frame.isAttackuping = false;
                player->frame.isDashing = false;
            }
            if (GetAsyncKeyState('C') & 0x8000 && !player->frame.isDashing) {
                player->frame.isDashing = true;
                player->frame.dashFrame = 0;
            }
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000 && !player->frame.isAttackuping) {
            player->frame.isAttackuping = true;
            player->frame.attackupFrame = 0;
        }
        if (GetAsyncKeyState('A') & 0x8000 && !player->frame.isAttackremoteing && player->state == PLAYER_STATE_DEFAULT) {
            player->frame.isAttackremoteing = true;
            player->frame.attackremoteFrame = 0;
            player->frame.ignoreKeys2 = true;
            player->box.velocity.x = 0;
            player->box.acceleration.x = 0;
            lastPressTimeU = currentTime;
        }
        if (GetAsyncKeyState('X') & 0x8000 && !player->frame.isAttacking) {
            player->frame.isAttacking = true;
            player->frame.attackFrame = 0;
        }
        if (GetAsyncKeyState('C') & 0x8000 && !player->frame.isDashing) {
            player->frame.isDashing = true;
            player->frame.dashFrame = 0;
        }
    }
    return 0;
}
