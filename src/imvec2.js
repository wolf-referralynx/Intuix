export class ImVec2 {
    constructor(x = 0, y = 0) {
        this.x = x;
        this.y = y;
    }

    // Adds another ImVec2 to this one
    add(vec) {
        return new ImVec2(this.x + vec.x, this.y + vec.y);
    }

    // Subtracts another ImVec2 from this one
    subtract(vec) {
        return new ImVec2(this.x - vec.x, this.y - vec.y);
    }

    // Multiplies this vector by a scalar
    multiplyScalar(scalar) {
        return new ImVec2(this.x * scalar, this.y * scalar);
    }

    // Divides this vector by a scalar
    divideScalar(scalar) {
        if (scalar === 0) {
            throw new Error("Cannot divide by zero.");
        }
        return new ImVec2(this.x / scalar, this.y / scalar);
    }

    // Dot product with another ImVec2
    dot(vec) {
        return this.x * vec.x + this.y * vec.y;
    }

    // Calculates the magnitude (length) of the vector
    magnitude() {
        return Math.sqrt(this.x ** 2 + this.y ** 2);
    }

    // Normalizes the vector (makes its length 1)
    normalize() {
        const mag = this.magnitude();
        if (mag === 0) {
            throw new Error("Cannot normalize a zero-length vector.");
        }
        return this.divideScalar(mag);
    }

    // Checks equality with another ImVec2
    equals(vec) {
        return this.x === vec.x && this.y === vec.y;
    }

    // Returns an array representation of the vector
    toArray() {
        return [this.x, this.y];
    }

    // Returns a string representation of the vector
    toString() {
        return `ImVec2(${this.x}, ${this.y})`;
    }

    // Creates a clone of this vector
    clone() {
        return new ImVec2(this.x, this.y);
    }

    // Reflects this vector over another vector
    reflect(normal) {
        const dot = this.dot(normal);
        return new ImVec2(
            this.x - 2 * dot * normal.x,
            this.y - 2 * dot * normal.y
        );
    }

    // Linearly interpolates between this vector and another
    lerp(vec, t) {
        return new ImVec2(
            this.x + t * (vec.x - this.x),
            this.y + t * (vec.y - this.y)
        );
    }

    // Rotates the vector by a specified angle (in radians)
    rotate(angle) {
        const cos = Math.cos(angle);
        const sin = Math.sin(angle);
        return new ImVec2(
            this.x * cos - this.y * sin,
            this.x * sin + this.y * cos
        );
    }
}
