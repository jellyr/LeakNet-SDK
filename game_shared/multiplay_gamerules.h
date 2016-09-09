//====== Copyright � 1996-2003, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#ifndef MULTIPLAY_GAMERULES_H
#define MULTIPLAY_GAMERULES_H
#ifdef _WIN32
#pragma once
#endif


#include "gamerules.h"


#ifdef CLIENT_DLL

	#define CMultiplayRules C_MultiplayRules

#endif


//=========================================================
// CMultiplayRules - rules for the basic half life multiplayer
// competition
//=========================================================
class CMultiplayRules : public CGameRules
{
public:
	DECLARE_CLASS( CMultiplayRules, CGameRules );
	DECLARE_NETWORKCLASS();

	virtual bool			ShouldCollide( int collisionGroup0, int collisionGroup1 );

#ifdef CLIENT_DLL

#else

	CMultiplayRules();
	virtual ~CMultiplayRules() {}

// GR_Think
	virtual void Think( void );
	virtual void RefreshSkillData( bool forceUpdate );
	virtual bool IsAllowedToSpawn( CBaseEntity *pEntity );
	virtual bool FAllowFlashlight( void );

	virtual bool FShouldSwitchWeapon( CBasePlayer *pPlayer, CBaseCombatWeapon *pWeapon );
	virtual CBaseCombatWeapon *GetNextBestWeapon( CBaseCombatCharacter *pPlayer, CBaseCombatWeapon *pCurrentWeapon );
	bool SwitchToNextBestWeapon( CBaseCombatCharacter *pPlayer, CBaseCombatWeapon *pCurrentWeapon );

// Functions to verify the single/multiplayer status of a game
	virtual bool IsMultiplayer( void );
	virtual bool IsDeathmatch( void );
	virtual bool IsCoOp( void );

// Client connection/disconnection
	// If ClientConnected returns FALSE, the connection is rejected and the user is provided the reason specified in
	//  svRejectReason
	// Only the client's name and remote address are provided to the dll for verification.
	virtual bool ClientConnected( edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[ 128 ] );
	virtual void InitHUD( CBasePlayer *pl );		// the client dll is ready for updating
	virtual void ClientDisconnected( edict_t *pClient );
	virtual void UpdateGameMode( CBasePlayer *pPlayer );  // the client needs to be informed of the current game mode

// Client damage rules
	virtual float FlPlayerFallDamage( CBasePlayer *pPlayer );
	virtual bool  FPlayerCanTakeDamage( CBasePlayer *pPlayer, CBaseEntity *pAttacker );

// Client spawn/respawn control
	virtual void PlayerSpawn( CBasePlayer *pPlayer );
	virtual void PlayerThink( CBasePlayer *pPlayer );
	virtual bool FPlayerCanRespawn( CBasePlayer *pPlayer );
	virtual float FlPlayerSpawnTime( CBasePlayer *pPlayer );
	virtual CBaseEntity *GetPlayerSpawnSpot( CBasePlayer *pPlayer );

	virtual bool AllowAutoTargetCrosshair( void );

// Client kills/scoring
	virtual int IPointsForKill( CBasePlayer *pAttacker, CBasePlayer *pKilled );
	virtual void PlayerKilled( CBasePlayer *pVictim, const CTakeDamageInfo &info );
	virtual void DeathNotice( CBasePlayer *pVictim, const CTakeDamageInfo &info );
	CBasePlayer *GetDeathScorer( CBaseEntity *pKiller, CBaseEntity *pInflictor );

// Weapon retrieval
	virtual bool CanHavePlayerItem( CBasePlayer *pPlayer, CBaseCombatWeapon *pWeapon );// The player is touching an CBaseCombatWeapon, do I give it to him?

// Weapon spawn/respawn control
	virtual int WeaponShouldRespawn( CBaseCombatWeapon *pWeapon );
	virtual float FlWeaponRespawnTime( CBaseCombatWeapon *pWeapon );
	virtual float FlWeaponTryRespawn( CBaseCombatWeapon *pWeapon );
	virtual Vector VecWeaponRespawnSpot( CBaseCombatWeapon *pWeapon );

// Item retrieval
	virtual bool CanHaveItem( CBasePlayer *pPlayer, CItem *pItem );
	virtual void PlayerGotItem( CBasePlayer *pPlayer, CItem *pItem );

// Item spawn/respawn control
	virtual int ItemShouldRespawn( CItem *pItem );
	virtual float FlItemRespawnTime( CItem *pItem );
	virtual Vector VecItemRespawnSpot( CItem *pItem );

// Ammo retrieval
	virtual void PlayerGotAmmo( CBaseCombatCharacter *pPlayer, char *szName, int iCount );

// Healthcharger respawn control
	virtual float FlHealthChargerRechargeTime( void );
	virtual float FlHEVChargerRechargeTime( void );

// What happens to a dead player's weapons
	virtual int DeadPlayerWeapons( CBasePlayer *pPlayer );

// What happens to a dead player's ammo	
	virtual int DeadPlayerAmmo( CBasePlayer *pPlayer );

// Teamplay stuff	
	virtual const char *GetTeamID( CBaseEntity *pEntity ) {return "";}
	virtual int PlayerRelationship( CBaseEntity *pPlayer, CBaseEntity *pTarget );
	virtual bool PlayerCanHearChat( CBasePlayer *pListener, CBasePlayer *pSpeaker );

	virtual bool PlayTextureSounds( void ) { return FALSE; }
	virtual bool PlayFootstepSounds( CBasePlayer *pl );

// NPCs
	virtual bool FAllowNPCs( void );

	// Immediately end a multiplayer game
	virtual void EndMultiplayerGame( void ) { GoToIntermission(); }

protected:
	virtual void ChangeLevel( void );
	virtual void GoToIntermission( void );
	float m_flIntermissionEndTime;
	bool m_iEndIntermissionButtonHit;
	void SendMOTDToClient( edict_t *client );
	
	virtual void			InitDefaultAIRelationships( void );
	virtual const char*		AIClassText(int classType);
	virtual const char *GetGameDescription( void ) { return "Half-Life 2: Deathmatch"; }

#endif
};


#endif // MULTIPLAY_GAMERULES_H