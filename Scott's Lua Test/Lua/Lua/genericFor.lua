fruit = { "Apple", "Banana", "Orange" }
colors = { ["Apple"] = "Red", ["Banana"] = "Yellow", ["Orange"] = "Orange" }

for idx,f in ipairs(fruit) do
  print(idx .. ": " .. f)
end

for f,col in pairs(colors) do
  print("The " .. f .. " is " .. col)
end
