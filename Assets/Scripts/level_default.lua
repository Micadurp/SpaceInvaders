level_default = {}

function level_default.LoadLevel()
	Game.CreatePlayer(400, 570)
	for i=1,9 do 
		for j=1,8 do 
			Game.CreateEnemy(225 + i * 40, j * 40)
		end
	end
	Game.PlaceWall(150, 500)
	Game.PlaceWall(350, 500)
	Game.PlaceWall(550, 500)
end

function level_default.Unload()
	
end

function level_default.Update(dt)
	
end
	