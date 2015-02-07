#include "gamerole.h"
#include "configure.h"
#include <QDebug>
#include "gamebullet.h"

GameRole::GameRole()
{
    this->RightKey = false;
    this->LeftKey = false;
    this->RightRelease = false;
    this->LeftRelease = false;
    this->UpKey = false;
    this->DownKey = false;
    this->UpRelease = false;
    this->DownRelease = false;
    this->RightKeyPress = false;
    this->LeftKeyPress = false;
    this->UpKeyPress = false;
    this->DownKeyPress = false;
    this->PixmapReflect = false;
    this->HP = 100;
    this->ixVer = 0;
    this->iyVer = 0;
    this->ABSx = 0;
    this->ABSy = 0;
    this->status = stand_status;
    this->last_status = stand_status;
    this->sprite_id = stand_sprite;
    this->motion_time_counter = 0;
}

GameRole::~GameRole()
{

}

void GameRole::SpriteChange(qint32 sprite)
{
    static bool isReflected = false;
    QPixmap temp;
    switch( sprite )
    {
    case walk_sprite :
        temp = this->sprite_walk;
    break;
    case walk2_sprite :
        temp = this->sprite_walk2;
    break;
    case walk3_sprite :
        temp = this->sprite_walk3;
    break;
    case jump_sprite :
        temp = this->sprite_jump;
    break;
    case null_sprite :
        this->SpriteChange(sprite_id);
    break;
    default:
        temp = this->sprite_stand;
    break;
    }
    if( sprite != null_sprite )
    {
        sprite_id = sprite;
    }
    if( this->PixmapReflect )
    {
        this->setPixmap(temp.transformed(QTransform().scale(-1, 1)));
    }
    else
    {
        this->setPixmap(temp);
    }
}

void GameRole::GameInit()
{
    this->RightKey = false;
    this->LeftKey = false;
    this->RightRelease = false;
    this->LeftRelease = false;
    this->UpKey = false;
    this->DownKey = false;
    this->UpRelease = false;
    this->DownRelease = false;
    this->RightKeyPress = false;
    this->LeftKeyPress = false;
    this->UpKeyPress = false;
    this->DownKeyPress = false;
    this->PixmapReflect = false;
    this->HP = 100;
    this->ixVer = 0;
    this->iyVer = 0;
    this->sprite = QPixmap(Config::FilePreix + "rockman.png");
    this->sprite_stand = this->sprite.copy(37,300,140,155);
    this->sprite_walk = this->sprite.copy(37,80,163,155);
    this->sprite_walk2 = this->sprite.copy(237,80,133,155);
    this->sprite_walk3 = this->sprite.copy(387,80,163,155);
    this->sprite_jump = this->sprite.copy(580,30,163,205);
    this->setPixmap( this->sprite_stand );
    this->setPos(300,700);
    this->ABSx = 300;
    this->ABSy = 700;
}

void GameRole::GameUpdate(qint64 delta)
{
    qreal ratio = qreal(delta)/100;
    last_status = status;
    Prex = ABSx;
    Prey = ABSy;
    ixAcc = 0;
    iyAcc = 0;

    InputDealer();


    if( ixVer > 0 )
    {
        if( ixVer < (50*ratio) )
            ixVer = 0;
        else
            ixVer = ixVer - (50*ratio);
    }

    else if( ixVer < 0 )
    {
        if( ixVer > (50*ratio) )
            ixVer = 0;
        else
            ixVer = ixVer + (50*ratio);
    }

    iyVer = iyVer + 60*ratio;

    if( this->iyVer > 0 && this->ABSy >= 700  )
        iyVer = 0;

    if( ixVer > 50 )ixVer = 50;
    else if( ixVer < -50 )ixVer = -50;

    this->ABSx = this->ABSx + ixVer * ratio;
    this->ABSy = this->ABSy + iyVer * ratio;
    if( this->ABSy > 700 ) {
        this->ABSy = 700 ;
        this->iyVer = 0;
    }

    if( this->RightRelease )
    {
        this->RightKey = false;
        this->RightRelease = false;
    }
    if( this->LeftRelease )
    {
        this->LeftKey = false;
        this->LeftRelease = false;
    }
    if( this->UpRelease )
    {
        this->UpKey = false;
        this->UpRelease = false;
    }
    if( this->DownRelease )
    {
        this->DownKey = false;
        this->DownRelease = false;
    }

    MotionUpdate(delta);
}

void GameRole::InputDealer()
{
    if( this->RightKey )
    {
        PixmapReflect = false;
        SpriteChange(this->sprite_id);
        ixAcc += 500;
    }
    if( this->LeftKey )
    {
        PixmapReflect = true;
        SpriteChange(this->sprite_id);
        ixAcc -= 500;
    }

    if( this->iyVer == 0 && this->ixVer == 0)
    {
        this->status = stand_status;
    }
    else if( this->iyVer == 0 )
    {
        this->status = walk_status;
    }
    if( this->UpKey && this->status != jump_status /*&& this->ABSy >= 700*/ && this->iyVer <= 0 )
    {
        iyAcc -= 160;
        this->status = jump_status;
    }
    ixVer += ixAcc ;
    iyVer += iyAcc ;
}

void GameRole::MotionUpdate(qint64 delta)
{
    if( this->last_status != this->status )
    {
        this->motion_time_counter = 0;
        switch(status)
        {
        case stand_status :
            this->SpriteChange(stand_sprite);
            break;
        case walk_status :
            this->SpriteChange(walk_sprite);
            break;
        case jump_status :
            this->SpriteChange(jump_sprite);
            break;
        }
    }
    else
    {
        this->motion_time_counter += delta;
        if( this->status == walk_status )
        {
            if( this->motion_time_counter % 600 > 450 )
            {
                this->SpriteChange(walk2_sprite);
            }
            else if( this->motion_time_counter % 600 > 300 )
            {
                this->SpriteChange(walk_sprite);
            }
            else if( this->motion_time_counter % 600 > 150 )
            {
                this->SpriteChange(walk2_sprite);
            }
            else
            {
                this->SpriteChange(walk3_sprite);
            }
        }
    }
}
