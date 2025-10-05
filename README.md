# NxNxN Rubik's cube simulator
This project simulates NxNxN Rubik's cubes, where N is a positive integer.

## The axis-offset movement notation
To allow moves on arbitrarily sized cubes, a new notation must be specified: an **axis**, an **offset** from the origin, and the **direction** of the rotation.

- **Axis:** one of the axes in the 3D coordinate space: **x**, **y**, or **z**.
- **Offset:** a nonnegative integer that specifies the splice (row or column) to rotate. Its value is the distance from the origin.
- **Origin:** The subcube that is found at the cube's leftmost column, lowest row, at the closest position. Its position doesn't change.
- **Direction:** a boolean flag that specifies whether to rotate the selected splice in a clockwise or a counter-clockwise direction. By default, it is set to **false**, meaning that rotation is done in a clockwise manner.

### Writing format

Using the axis-offset notation, moves are written in the following format:

`<axis><offset>[<counter-clockwise>]`, where
- **axis** is the letter **x**, **y**, or **z**
- **offset** is an arbitrary nonnegative integer
- **counter-clockwise** is an optional `'` character (single-quote)

#### Examples:
- `x0`: Rotate the **first layer** from the origin in the **x-axis** in a **clockwise** direction.
- `x0'`: Rotate the **first layer** from the origin in the **x-axis** in a **counter-clockwise** direction.
- `y11`: Rotate the **twelfth layer** from the origin in the **y-axis** in a **clockwise** direction.
- `z2'`: Rotate the **third** layer from the origin in the **z-axis** in a **counter-clockwise** direction.

> [!NOTE]
> Offsets start from zero.

### Translation from traditional notation
Each traditional move has an **axis-offset** counterpart.

In 2x2x2 cubes, the translation is as follows:

|Traditional|Axis-offset|
|-----------|------------|
|U|z1'|
|U'|z1|
|D|z0|
|D'|z0'|
|L|x0|
|L'|x0'|
|R|x1'|
|R'|x1|
|F|y0|
|F'|y0'|
|B|y1'|
|B'|y1|
