function Load()
	dofile( "Scripts/level_default.lua" )
	level_default.LoadLevel()
end

function Unload()
	level_default.Unload()
end

function Update(dt)
	level_default.Update(dt)
	Game.InputCheck(dt)
end