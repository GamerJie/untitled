
local entity = require "data.entity.player"

local player
local enemy
local sprite
local transform
local speed = 200

local isRun = false
local dir = { x = 0, y = 0}


function setup()
	player = world:create()
	player.name = "player"
	player:addCom(entity.components)

	enemy = world:create()
end


function update(dt)
	dir = { x = 0, y = 0}
	
	if key_down(Key.W) then
		dir.y = -1
	end
	
	if key_down(Key.S) then
		dir.y = 1
	end
	
	if key_down(Key.D) then
		dir.x = 1
	end
	
	if key_down(Key.A) then
		dir.x = -1
	end
	
	if dir.x ~= 0 then
		player:setScale(dir.x * 2, player:getScale().y)
	end
	
	player:translate(speed * dir.x * dt, speed * dir.y * dt)
	
	isRun = dir.x ~= 0 or dir.y ~= 0
	player:updateAnimation(isRun and "run" or "idle")
end