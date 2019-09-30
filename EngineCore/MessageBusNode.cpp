//STD Headers
#include <memory>
#include <iostream>

//Library Headers


//Coati Headers
#include "MessageBusNode.h"
#include "MessageBus.h"
#include "Message.h"
#include "EventTable.h"

namespace core {

	MessageBusNode::MessageBusNode(std::shared_ptr<MessageBus> messageBus) 
		: GameMessageBus(std::move(messageBus)) {

		if (!this->GameMessageBus) {
			std::cout << "no message bus";
		}
	}

	MessageBusNode::~MessageBusNode() {
		UnregisterReciever();
	}

	// Protected Member Functions

	void MessageBusNode::RegisterReciever() {
		GameMessageBus->AddReceiver(this, MessageType::NACK);
	}

	void MessageBusNode::UnregisterReciever() {
		GameMessageBus->RemoveReceiver(this);
	}

	void MessageBusNode::PublishMessage(const std::string &message, const MessageType &type) {
		Message outgoing(message, type);
		GameMessageBus->PublishMessage(outgoing);
	}

	void MessageBusNode::PublishMessage(const Message &message) {
		GameMessageBus->PublishMessage(message);
	}

	void MessageBusNode::ReceiveMessage(const Message& message) {
		if (Events[message]) {
			Events[message]();
		}
	}

}