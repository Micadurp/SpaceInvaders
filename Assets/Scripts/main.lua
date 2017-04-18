G_ENEMY_AMOUNT = 0;
G_WALL_AMOUNT = 0;
G_BULLET_AMOUNT = 0;

function Load()
	dofile( "Scripts/level_default.lua" )
	level_default.LoadLevel()
	G_ENEMY_AMOUNT = Game.GetTotalEnemies();
	G_WALL_AMOUNT = Game.GetTotalWalls();
	G_BULLET_AMOUNT = Game.GetTotalBullets();
	dofile( "Scripts/bullet_check.lua" )
	bullet_check.Load()
end

function Unload()
	level_default.Unload()
end

function Update(dt)
	level_default.Update(dt)
	Game.InputCheck(dt)
	bullet_check.Update(dt)
end