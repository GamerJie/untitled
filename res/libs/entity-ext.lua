
function Entity:get(com)
	if com == TransformCom then
		local c = self:getCom(com)
		return Transform.get(c)
	elseif com == SpriteCom then
		local c = self:getCom(com)
		return Sprite.get(c)
	end
end

function Entity:translate(pos, y)
	local transform = self:get(TransformCom)
	if transform == nil then
		return
	end
	
	if type(pos) == "table" then
		transform.position.x = transform.position.x + pos.x
		transform.position.y = transform.position.y + pos.y
	elseif type(pos) == "number" and type(y) == "number" then
		transform.position.x = transform.position.x + pos
		transform.position.y = transform.position.y + y
	end
end

function Entity:getPos()
	local transform = self:get(TransformCom)
	if transform ~= nil then
		return transform.position
	end
end

function Entity:setPos(pos, y)
	local transform = self:get(TransformCom)
	if transform == nil then
		return
	end
	
	if type(pos) == "table" then
		transform.position.x = pos.x
		transform.position.y = pos.y
	elseif type(pos) == "number" and type(y) == "number" then
		transform.position.x = pos
		transform.position.y = y
	end
end

function Entity:getScale()
	local transform = self:get(TransformCom)
	if transform == nil then
		return
	end
	
	return transform.scale
end

function Entity:setScale(pos, y)
	local transform = self:get(TransformCom)
	if transform == nil then
		return
	end
	
	if type(pos) == "table" then
		transform.scale.x = pos.x
		transform.scale.y = pos.y
	elseif type(pos) == "number" and type(y) == "number" then
		transform.scale.x = pos
		transform.scale.y = y
	end
end

function Entity:updateAnimation(name)
	local sprite = self:get(SpriteCom)
	if sprite == nil then
		return
	end
	
	sprite:update(name)
end

