
function Damage (health, damage)
	health = health - damage
	return health
end

component = {
	isIO = { 
		name,
		data
	},

	isSoundEffect = {
		name,
		soundEffect
	},

	isSprite = {
		name,
		texture, 
		boxes
	},

	isStringTable = {
		name
	},

	isPhysics = {
		name,
		world,
		bodyDef,
		fixDef
	}
}

function ComponentIsIO (isIO)
	if component["isIO"]["data"] == NIL then
		return false
	else 
		return true
	end
end

function ComponentIsSoundEffect (isSoundEffect)
	if component["isSoundEffect"]["soundEffect"] == NIL then
		return false
	else
		return true
	end
end

function ComponentIsSprite (isSprite)
	if component["isSprite"]["texture"] == NIL | component["isSprite"]["boxes"] == NIL then
		return false
	else
		return true
	end
end

function ComponentIsPhysics (isPhysics)
	if component["isPhysics"]["world"] == NIL | component["isPhysics"]["bodyDef"] == NIL | component["isPhysics"]["fixDef"] == NIL then
		return false
	else 
		return true
	end
end

function Component (component) 
	if ComponentIsIO(component["isIO"]) == true then
		return "IO"
	else if ComponentIsSoundEffect(component["isSoundEffect"]) == true then
		return "soundEffect"
	else if ComponentIsSprite(component["isSprite"]) == true then
		return "sprite"
	else if ComponentIsPhysics(component["isPhysics"]) == true then
		return "physics"
	end
	end
	end
	end
end
