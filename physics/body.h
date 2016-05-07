/*
 * Interface file for the rigid body class.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

/**
 * @file
 *
 * This file contains the definitions for the rigid body class, the
 * basic building block of all the physics system.
 */
#ifndef CYCLONE_BODY_H
#define CYCLONE_BODY_H

#include "core.h"

//namespace cyclone {

    /**
     * A rigid body is the basic simulation object in the physics
     * core.
     *
     * It has position and orientation data, along with first
     * derivatives. It can be integrated forward through time, and
     * have forces, torques and impulses (linear or angular) applied
     * to it. The rigid body manages its state and allows access
     * through a set of methods.
     *
     * A ridid body contains 64 words (the size of which is given
     * by the precision: sizeof(real)). It contains no virtual
     * functions, so should take up exactly 64 words in memory. Of
     * this total 15 words are padding, distributed among the
     * Vector3 data members.
     */
    class RigidBody
    {
    public:

        // ... Other RigidBody code as before ...


    protected:

		/**
		* Holds the inverse of the mass of the rigid body. It
		* is more useful to hold the inverse mass because
		* integration is simpler, and because in real time
		* simulation it is more useful to have bodies with
		* infinite mass (immovable) than zero mass
		* (completely unstable in numerical simulation).
		*/
		real inverseMass;

		/**
		* Holds the inverse of the body's inertia tensor. The
		* inertia tensor provided must not be degenerate
		* (that would mean the body had zero inertia for
		* spinning along one axis). As long as the tensor is
		* finite, it will be invertible. The inverse tensor
		* is used for similar reasons to the use of inverse
		* mass.
		*
		* The inertia tensor, unlike the other variables that
		* define a rigid body, is given in body space.
		*
		* @see inverseMass
		*/
		Matrix3 inverseInertiaTensor;

        /**
         * Holds the amount of damping applied to linear
         * motion.  Damping is required to remove energy added
         * through numerical instability in the integrator.
         */
        real linearDamping;

        /**
         * Holds the amount of damping applied to angular
         * motion.  Damping is required to remove energy added
         * through numerical instability in the integrator.
         */
        real angularDamping;

        /**
         * Holds the linear position of the rigid body in
         * world space.
         */
        Vector3 position;

        /**
         * Holds the angular orientation of the rigid body in
         * world space.
         */
        Quaternion orientation;

        /**
         * Holds the linear velocity of the rigid body in
         * world space.
         */
        Vector3 velocity;

        /**
         * Holds the angular velocity, or rotation, or the
         * rigid body in world space.
         */
        Vector3 rotation;

		/**
		* Holds the inverse inertia tensor of the body in world
		* space. The inverse inertia tensor member is specified in
		* the body's local space.
		*
		* @see inverseInertiaTensor
		*/
		Matrix3 inverseInertiaTensorWorld;
       
        /**
         * Holds a transform matrix for converting body space into
         * world space and vice versa. This can be achieved by calling
         * the getPointIn*Space functions.
         *
         * @see getPointInLocalSpace
         * @see getPointInWorldSpace
         * @see getTransform
         */
        Matrix4 transformMatrix;


       /**
         * Holds the acceleration of the rigid body.  This value
         * can be used to set acceleration due to gravity (its primary
         * use), or any other constant acceleration.
         */
        Vector3 acceleration;

        /**
         * Holds the linear acceleration of the rigid body, for the
         * previous frame.
         */
        Vector3 lastFrameAcceleration;

        /*@}*/

    public:
        /**
         * @name Constructor and Destructor
         *
         * There are no data members in the rigid body class that are
         * created on the heap. So all data storage is handled
         * automatically.
         */
        /*@{*/

        /*@}*/


        /**
         * @name Integration and Simulation Functions
         *
         * These functions are used to simulate the rigid body's
         * motion over time. A normal application sets up one or more
         * rigid bodies, applies permanent forces (i.e. gravity), then
         * adds transient forces each frame, and integrates, prior to
         * rendering.
         *
         * Currently the only integration function provided is the
         * first order Newton Euler method.
         */
        /*@{*/

        /**
         * Calculates internal data from state data. This should be called
         * after the body's state is altered directly (it is called
         * automatically during integration). If you change the body's state
         * and then intend to integrate before querying any data (such as
         * the transform matrix), then you can ommit this step.
         */
        void calculateDerivedData();

        /**
         * Integrates the rigid body forward in time by the given amount.
         * This function uses a Newton-Euler integration method, which is a
         * linear approximation to the correct integral. For this reason it
         * may be inaccurate in some cases.
         */
        void integrate(real duration);

        /*@}*/

		/**
		* Sets the mass of the rigid body.
		*
		* @param mass The new mass of the body. This may not be zero.
		* Small masses can produce unstable rigid bodies under
		* simulation.
		*
		* @warning This invalidates internal data for the rigid body.
		* Either an integration function, or the calculateInternals
		* function should be called before trying to get any settings
		* from the rigid body.
		*/
		void setMass(const real mass);

		/**
		* Gets the mass of the rigid body.
		*
		* @return The current mass of the rigid body.
		*/
		real getMass() const;

		/**
		* Sets the inverse mass of the rigid body.
		*
		* @param inverseMass The new inverse mass of the body. This
		* may be zero, for a body with infinite mass
		* (i.e. unmovable).
		*
		* @warning This invalidates internal data for the rigid body.
		* Either an integration function, or the calculateInternals
		* function should be called before trying to get any settings
		* from the rigid body.
		*/
		void setInverseMass(const real inverseMass);

		/**
		* Gets the inverse mass of the rigid body.
		*
		* @return The current inverse mass of the rigid body.
		*/
		real getInverseMass() const;

		/**
		* Returns true if the mass of the body is not-infinite.
		*/
		bool hasFiniteMass() const;



		/**
		* Sets the intertia tensor for the rigid body.
		*
		* @param inertiaTensor The inertia tensor for the rigid
		* body. This must be a full rank matrix and must be
		* invertible.
		*
		* @warning This invalidates internal data for the rigid body.
		* Either an integration function, or the calculateInternals
		* function should be called before trying to get any settings
		* from the rigid body.
		*/
		void setInertiaTensor(const Matrix3 &inertiaTensor);

		/**
		* Copies the current inertia tensor of the rigid body into
		* the given matrix.
		*
		* @param inertiaTensor A pointer to a matrix to hold the
		* current inertia tensor of the rigid body. The inertia
		* tensor is expressed in the rigid body's local space.
		*/
		void getInertiaTensor(Matrix3 *inertiaTensor) const;

		/**
		* Gets a copy of the current inertia tensor of the rigid body.
		*
		* @return A new matrix containing the current intertia
		* tensor. The inertia tensor is expressed in the rigid body's
		* local space.
		*/
		Matrix3 getInertiaTensor() const;

		/**
		* Copies the current inertia tensor of the rigid body into
		* the given matrix.
		*
		* @param inertiaTensor A pointer to a matrix to hold the
		* current inertia tensor of the rigid body. The inertia
		* tensor is expressed in world space.
		*/
		void getInertiaTensorWorld(Matrix3 *inertiaTensor) const;

		/**
		* Gets a copy of the current inertia tensor of the rigid body.
		*
		* @return A new matrix containing the current intertia
		* tensor. The inertia tensor is expressed in world space.
		*/
		Matrix3 getInertiaTensorWorld() const;

		/**
		* Sets the inverse intertia tensor for the rigid body.
		*
		* @param inverseInertiaTensor The inverse inertia tensor for
		* the rigid body. This must be a full rank matrix and must be
		* invertible.
		*
		* @warning This invalidates internal data for the rigid body.
		* Either an integration function, or the calculateInternals
		* function should be called before trying to get any settings
		* from the rigid body.
		*/
		void setInverseInertiaTensor(const Matrix3 &inverseInertiaTensor);

		/**
		* Copies the current inverse inertia tensor of the rigid body
		* into the given matrix.
		*
		* @param inverseInertiaTensor A pointer to a matrix to hold
		* the current inverse inertia tensor of the rigid body. The
		* inertia tensor is expressed in the rigid body's local
		* space.
		*/
		void getInverseInertiaTensor(Matrix3 *inverseInertiaTensor) const;

		/**
		* Gets a copy of the current inverse inertia tensor of the
		* rigid body.
		*
		* @return A new matrix containing the current inverse
		* intertia tensor. The inertia tensor is expressed in the
		* rigid body's local space.
		*/
		Matrix3 getInverseInertiaTensor() const;

		/**
		* Copies the current inverse inertia tensor of the rigid body
		* into the given matrix.
		*
		* @param inverseInertiaTensor A pointer to a matrix to hold
		* the current inverse inertia tensor of the rigid body. The
		* inertia tensor is expressed in world space.
		*/
		void getInverseInertiaTensorWorld(Matrix3 *inverseInertiaTensor) const;

		/**
		* Gets a copy of the current inverse inertia tensor of the
		* rigid body.
		*
		* @return A new matrix containing the current inverse
		* intertia tensor. The inertia tensor is expressed in world
		* space.
		*/
		Matrix3 getInverseInertiaTensorWorld() const;




        
        /**
         * Sets both linear and angular damping in one function call.
         *
         * @param linearDamping The speed that velocity is shed from
         * the rigid body.
         *
         * @param angularDamping The speed that rotation is shed from
         * the rigid body.
         *
         * @see setLinearDamping
         * @see setAngularDamping
         */
        void setDamping(const real linearDamping, const real angularDamping);

        /**
         * Sets the linear damping for the rigid body.
         *
         * @param linearDamping The speed that velocity is shed from
         * the rigid body.
         *
         * @see setAngularDamping
         */
        void setLinearDamping(const real linearDamping);

        /**
         * Gets the current linear damping value.
         *
         * @return The current linear damping value.
         */
        real getLinearDamping() const;

        /**
         * Sets the angular damping for the rigid body.
         *
         * @param angularDamping The speed that rotation is shed from
         * the rigid body.
         *
         * @see setLinearDamping
         */
        void setAngularDamping(const real angularDamping);

        /**
         * Gets the current angular damping value.
         *
         * @return The current angular damping value.
         */
        real getAngularDamping() const;

        /**
         * Sets the position of the rigid body.
         *
         * @param position The new position of the rigid body.
         */
        void setPosition(const Vector3 &position);

        /**
         * Sets the position of the rigid body by component.
         *
         * @param x The x coordinate of the new position of the rigid
         * body.
         *
         * @param y The y coordinate of the new position of the rigid
         * body.
         *
         * @param z The z coordinate of the new position of the rigid
         * body.
         */
        void setPosition(const real x, const real y, const real z);

        /**
         * Fills the given vector with the position of the rigid body.
         *
         * @param position A pointer to a vector into which to write
         * the position.
         */
        void getPosition(Vector3 *position) const;

        /**
         * Gets the position of the rigid body.
         *
         * @return The position of the rigid body.
         */
        Vector3 getPosition() const;

        /**
         * Sets the orientation of the rigid body.
         *
         * @param orientation The new orientation of the rigid body.
         *
         * @note The given orientation does not need to be normalised,
         * and can be zero. This function automatically constructs a
         * valid rotation quaternion with (0,0,0,0) mapping to
         * (1,0,0,0).
         */
        void setOrientation(const Quaternion &orientation);

        /**
         * Sets the orientation of the rigid body by component.
         *
         * @param r The real component of the rigid body's orientation
         * quaternion.
         *
         * @param i The first complex component of the rigid body's
         * orientation quaternion.
         *
         * @param j The second complex component of the rigid body's
         * orientation quaternion.
         *
         * @param k The third complex component of the rigid body's
         * orientation quaternion.
         *
         * @note The given orientation does not need to be normalised,
         * and can be zero. This function automatically constructs a
         * valid rotation quaternion with (0,0,0,0) mapping to
         * (1,0,0,0).
         */
        void setOrientation(const real r, const real i,
            const real j, const real k);

        /**
         * Fills the given quaternion with the current value of the
         * rigid body's orientation.
         *
         * @param orientation A pointer to a quaternion to receive the
         * orientation data.
         */
        void getOrientation(Quaternion *orientation) const;

        /**
         * Gets the orientation of the rigid body.
         *
         * @return The orientation of the rigid body.
         */
        Quaternion getOrientation() const;

        /**
         * Fills the given matrix with a transformation representing
         * the rigid body's orientation.
         *
         * @note Transforming a direction vector by this matrix turns
         * it from the body's local space to world space.
         *
         * @param matrix A pointer to the matrix to fill.
         */
        void getOrientation(Matrix3 *matrix) const;

        /**
         * Fills the given matrix data structure with a transformation
         * representing the rigid body's orientation.
         *
         * @note Transforming a direction vector by this matrix turns
         * it from the body's local space to world space.
         *
         * @param matrix A pointer to the matrix to fill.
         */
        void getOrientation(real matrix[9]) const;

        /**
         * Fills the given matrix with a transformation representing
         * the rigid body's position and orientation.
         *
         * @note Transforming a vector by this matrix turns it from
         * the body's local space to world space.
         *
         * @param transform A pointer to the matrix to fill.
         */
        void getTransform(Matrix4 *transform) const;

        /**
         * Fills the given matrix data structure with a
         * transformation representing the rigid body's position and
         * orientation.
         *
         * @note Transforming a vector by this matrix turns it from
         * the body's local space to world space.
         *
         * @param matrix A pointer to the matrix to fill.
         */
        void getTransform(real matrix[16]) const;

        /**
         * Fills the given matrix data structure with a
         * transformation representing the rigid body's position and
         * orientation. The matrix is transposed from that returned
         * by getTransform. This call returns a matrix suitable
         * for applying as an OpenGL transform.
         *
         * @note Transforming a vector by this matrix turns it from
         * the body's local space to world space.
         *
         * @param matrix A pointer to the matrix to fill.
         */
        void getGLTransform(float matrix[16]) const;

        /**
         * Gets a transformation representing the rigid body's
         * position and orientation.
         *
         * @note Transforming a vector by this matrix turns it from
         * the body's local space to world space.
         *
         * @return The transform matrix for the rigid body.
         */
        Matrix4 getTransform() const;

        /**
         * Converts the given point from world space into the body's
         * local space.
         *
         * @param point The point to covert, given in world space.
         *
         * @return The converted point, in local space.
         */
        Vector3 getPointInLocalSpace(const Vector3 &point) const;

        /**
         * Converts the given point from world space into the body's
         * local space.
         *
         * @param point The point to covert, given in local space.
         *
         * @return The converted point, in world space.
         */
        Vector3 getPointInWorldSpace(const Vector3 &point) const;

        /**
         * Converts the given direction from world space into the
         * body's local space.
         *
         * @note When a direction is converted between frames of
         * reference, there is no translation required.
         *
         * @param direction The direction to covert, given in world
         * space.
         *
         * @return The converted direction, in local space.
         */
        Vector3 getDirectionInLocalSpace(const Vector3 &direction) const;

        /**
         * Converts the given direction from world space into the
         * body's local space.
         *
         * @note When a direction is converted between frames of
         * reference, there is no translation required.
         *
         * @param direction The direction to covert, given in local
         * space.
         *
         * @return The converted direction, in world space.
         */
        Vector3 getDirectionInWorldSpace(const Vector3 &direction) const;

        /**
         * Sets the velocity of the rigid body.
         *
         * @param velocity The new velocity of the rigid body. The
         * velocity is given in world space.
         */
        void setVelocity(const Vector3 &velocity);

        /**
         * Sets the velocity of the rigid body by component. The
         * velocity is given in world space.
         *
         * @param x The x coordinate of the new velocity of the rigid
         * body.
         *
         * @param y The y coordinate of the new velocity of the rigid
         * body.
         *
         * @param z The z coordinate of the new velocity of the rigid
         * body.
         */
        void setVelocity(const real x, const real y, const real z);

        /**
         * Fills the given vector with the velocity of the rigid body.
         *
         * @param velocity A pointer to a vector into which to write
         * the velocity. The velocity is given in world local space.
         */
        void getVelocity(Vector3 *velocity) const;

        /**
         * Gets the velocity of the rigid body.
         *
         * @return The velocity of the rigid body. The velocity is
         * given in world local space.
         */
        Vector3 getVelocity() const;

        /**
         * Applies the given change in velocity.
         */
        void addVelocity(const Vector3 &deltaVelocity);

        /**
         * Sets the rotation of the rigid body.
         *
         * @param rotation The new rotation of the rigid body. The
         * rotation is given in world space.
         */
        void setRotation(const Vector3 &rotation);

        /**
         * Sets the rotation of the rigid body by component. The
         * rotation is given in world space.
         *
         * @param x The x coordinate of the new rotation of the rigid
         * body.
         *
         * @param y The y coordinate of the new rotation of the rigid
         * body.
         *
         * @param z The z coordinate of the new rotation of the rigid
         * body.
         */
        void setRotation(const real x, const real y, const real z);

        /**
         * Fills the given vector with the rotation of the rigid body.
         *
         * @param rotation A pointer to a vector into which to write
         * the rotation. The rotation is given in world local space.
         */
        void getRotation(Vector3 *rotation) const;

        /**
         * Gets the rotation of the rigid body.
         *
         * @return The rotation of the rigid body. The rotation is
         * given in world local space.
         */
        Vector3 getRotation() const;

        /**
         * Applies the given change in rotation.
         */
        void addRotation(const Vector3 &deltaRotation);

		/**
		* Fills the given vector with the current accumulated value
		* for linear acceleration. The acceleration accumulators
		* are set during the integration step. They can be read to
		* determine the rigid body's acceleration over the last
		* integration step. The linear acceleration is given in world
		* space.
		*
		* @param linearAcceleration A pointer to a vector to receive
		* the linear acceleration data.
		*/
		void getLastFrameAcceleration(Vector3 *linearAcceleration) const;

		/**
		* Gets the current accumulated value for linear
		* acceleration. The acceleration accumulators are set during
		* the integration step. They can be read to determine the
		* rigid body's acceleration over the last integration
		* step. The linear acceleration is given in world space.
		*
		* @return The rigid body's linear acceleration.
		*/
		Vector3 getLastFrameAcceleration() const;

        /**
         * Sets the constant acceleration of the rigid body.
         *
         * @param acceleration The new acceleration of the rigid body.
         */
        void setAcceleration(const Vector3 &acceleration);

        /**
         * Sets the constant acceleration of the rigid body by component.
         *
         * @param x The x coordinate of the new acceleration of the rigid
         * body.
         *
         * @param y The y coordinate of the new acceleration of the rigid
         * body.
         *
         * @param z The z coordinate of the new acceleration of the rigid
         * body.
         */
        void setAcceleration(const real x, const real y, const real z);

        /**
         * Fills the given vector with the acceleration of the rigid body.
         *
         * @param acceleration A pointer to a vector into which to write
         * the acceleration. The acceleration is given in world local space.
         */
        void getAcceleration(Vector3 *acceleration) const;

        /**
         * Gets the acceleration of the rigid body.
         *
         * @return The acceleration of the rigid body. The acceleration is
         * given in world local space.
         */
        Vector3 getAcceleration() const;

        /*@}*/

    };

//} // namespace cyclone

#endif // CYCLONE_BODY_H
