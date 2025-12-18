#include "RigidParticle.h"
#include "RenderUtils.hpp"
#include <iostream>

// Variables globales de PhysX
extern physx::PxScene* gScene;
extern physx::PxPhysics* gPhysics;
extern physx::PxMaterial* gMaterial;
RigidParticle::RigidParticle(const RIGID_BODY_PROPS& props, physx::PxMaterial* mat) : _rb(nullptr), _renderItem(nullptr) {
    if (!mat) mat = gMaterial;

    // Validación de PhysX
    if (!gPhysics || !gScene || !gMaterial) {
        std::cerr << "ERROR: PhysX no está inicializado" << std::endl;
        return;
    }

    try {
        physx::PxGeometry* geo = nullptr;
        
        // Crear geometría
        if (props._shapeType == "SPHERE") {
            geo = new physx::PxSphereGeometry(props._sizeX);
        } 
        else if (props._shapeType == "BOX") {
            geo = new physx::PxBoxGeometry(props._sizeX, props._sizeY, props._sizeZ);
        } 
        else {
            geo = new physx::PxSphereGeometry(props._sizeX);
        }

        // Crear cuerpo rígido
        if (props._isDynamic) {
            _rb = gPhysics->createRigidDynamic(physx::PxTransform(props._transform));
            if (_rb) {
                auto dyn = static_cast<physx::PxRigidDynamic*>(_rb);
                dyn->setLinearVelocity(props._velocity);
                dyn->setMass(props._mass);
                dyn->setLinearDamping(0.5f);
                dyn->setAngularDamping(0.5f);
            }
        } 
        else {
            _rb = gPhysics->createRigidStatic(physx::PxTransform(props._transform));
        }

        if (!_rb) {
            std::cerr << "ERROR: No se pudo crear el cuerpo rígido" << std::endl;
            delete geo;
            return;
        }

        // Crear forma y adjuntarla
        physx::PxShape* shape = gPhysics->createShape(*geo, *mat);
        _rb->attachShape(*shape);
        shape->release(); // Importante: liberar referencia

        // Añadir a la escena
        gScene->addActor(*_rb);

        // Crear RenderItem
        physx::PxShape* renderShape = nullptr;
        _rb->getShapes(&renderShape, 1);
        
        if (renderShape) {
            // Usar NEW para RenderItem que será manejado por el sistema de renderizado
            _renderItem = new RenderItem(renderShape, _rb, props.color);
        }

        delete geo;

    } catch (...) {
        std::cerr << "EXCEPCIÓN al crear RigidParticle" << std::endl;
        if (_rb) {
            _rb->release();
            _rb = nullptr;
        }
    }

    // Inicializar miembros
    _mass = props._mass;
    _lifeTime = props._lifeTime;
    _size = props._sizeX;
    _shapeType = props._shapeType;
}

RigidParticle::~RigidParticle() {
    delete _renderItem;
    _renderItem = nullptr;
    if (_rb) {
        try {
            if (gScene) gScene->removeActor(*_rb);
            
            _rb->release();
            _rb = nullptr;
        } catch (...) {
            std::cerr << "Error al destruir RigidParticle" << std::endl;
        }
    }
}

void RigidParticle::integrate(double t) {
    
    _lifeTime -= t;
}

void RigidParticle::addForce(const Vector3& force) {
    if (_rb && _rb->is<physx::PxRigidDynamic>()) {
        static_cast<physx::PxRigidDynamic*>(_rb)->addForce(physx::PxVec3(force.x, force.y, force.z));
    }
}

void RigidParticle::addTorque(const Vector3& torque) {
    if (_rb && _rb->is<physx::PxRigidDynamic>()) {
        static_cast<physx::PxRigidDynamic*>(_rb)->addTorque(physx::PxVec3(torque.x, torque.y, torque.z));
    }
}

Vector3 RigidParticle::getPosition() const {
    if (_rb) {
        try {
            physx::PxVec3 pos = _rb->getGlobalPose().p;
            return Vector3(pos.x, pos.y, pos.z);
        } catch (...) {
            std::cerr << "Error al obtener posición de RigidParticle" << std::endl;
            return Vector3(0, 0, 0);
        }
    }
    std::cerr << "Warning: Intento de obtener posición de RigidParticle nulo" << std::endl;
    return Vector3(0, 0, 0);
}

Vector3 RigidParticle::getVelocity() const {
    if (_rb && _rb->is<physx::PxRigidDynamic>()) {
        try {
            physx::PxVec3 vel = static_cast<physx::PxRigidDynamic*>(_rb)->getLinearVelocity();
            return Vector3(vel.x, vel.y, vel.z);
        } catch (...) {
            std::cerr << "Error al obtener velocidad de RigidParticle" << std::endl;
        }
    }
    return Vector3(0, 0, 0);
}

bool RigidParticle::isDynamic() const {
    return _rb && _rb->is<physx::PxRigidDynamic>();
}