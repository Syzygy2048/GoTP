#include "UIView.h"
#include "..\InputHandlerSFML.h"
#include "..\UIViewListener.h"
#include "..\InputHandlerSFML.h"
#include "..\AssetManager.h"
#include "..\FocusGroup.h"

UIView::UIView(sf::Vector2i* newSize, std::string newTexture)
{
	configInitialSettings(newSize);

	setTexture(newTexture);
}

UIView::UIView(sf::Vector2i* newSize)
{
	configInitialSettings(newSize);
}

UIView::~UIView(void)
{
	if (finalTexture)
	{
		delete finalTexture;
	}

	if (text)
	{
		delete text;
	}

	if (size)
	{
		delete size;
	}

	if(group)
	{
		group->removeFocusable(this);
	}
}

void UIView::setUIViewListener(UIViewListener* newListener)
{
	listener = newListener;
}

void UIView::activated(int key)
{
	if(listener)
	{
		listener->viewClicked(this,key);
	}
}

void UIView::setHoveredState(bool hoveredState)
{
	beingHovered = hoveredState;

	if (listener)
	{
		listener->viewHovered(this, beingHovered);
	}
}

void UIView::setFocusedState(bool newFocusState)
{
	focusedState = newFocusState;

	if(listener)
	{
		listener->viewFocused(this, focusedState);
	}
}

void UIView::setDrawAsPanel(bool newDrawAsPanel)
{
	drawAsPanel = newDrawAsPanel;

	adjustBackGround();
}

void UIView::setText(sf::Text* newText)
{
	if (text)
	{
		delete text;
	}

	text = newText;

	adjustBackGround();
}

void UIView::updateText(sf::String newString)
{
	if(text)
	{
		text->setString(newString);

		adjustBackGround();
	}
	else
	{
		std::cout<<"Can´t update text "<<newString.toAnsiString() <<" because the text is null.\nYou dumbass.\n";
	}
}

void UIView::setSize(sf::Vector2i* newSize)
{
	size = newSize;

	adjustBackGround();
}

void UIView::onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform)
{
	SpriteNode::onDraw(deltaTime,target, parentTranform);

	if(ignoreMouse)
	{
		return;
	}

	sf::FloatRect rect = sf::FloatRect(float(-size->x)/2+offset->x,float(-size->y)/2,float(size->x),float(size->y)+offset->y);

	sf::Transform inverse = parentTranform.getInverse();

	sf::Vector2i mousePos = *InputHandlerSFML::getInstance()->getMousePosition();

	sf::Vector2f transformedPoint = inverse.transformPoint(float(mousePos.x),float(mousePos.y));

	if(rect.contains(transformedPoint))
	{
		InputHandlerSFML::getInstance()->setDrawnClickable(this);
	}
}

//Black magic that will set the proper image. Forgot how it works exactly.
void UIView::adjustBackGround()
{
	if (!drawAsPanel)
	{
		//it may be bugged as fuck.
		sf::RenderTexture* destinationTexture = new sf::RenderTexture();

		destinationTexture->create(size->x,size->y);

		destinationTexture->setSmooth(true);

		destinationTexture->clear(sf::Color::Transparent);

		if(texture)
		{
			sf::Sprite tempSprite = sf::Sprite();

			tempSprite.setScale(float(size->x)/texture->getSize().x,float(size->y)/texture->getSize().y);

			tempSprite.setTexture(*texture);

			destinationTexture->draw(tempSprite);
		}
		if(text)
		{
			destinationTexture->draw(*text);
		}

		if(finalTexture)
		{
			sprite->move(float(finalTexture->getSize().x)/2,float((finalTexture->getSize().y)/2));

			delete finalTexture;
		}

		destinationTexture->display();

		finalTexture = new sf::Texture(destinationTexture->getTexture());

		delete destinationTexture;

		finalTexture->setSmooth(true);

		sprite->setTexture(*finalTexture);

		sprite->move(-float(finalTexture->getSize().x)/2,-float((finalTexture->getSize().y)/2));

		return;
	}

	sprite->setScale(1,1);

	sf::RenderTexture* destinationTexture =new sf::RenderTexture();

	destinationTexture->create(size->x,size->y);

	destinationTexture->setSmooth(true);

	if(texture)
	{
		int tileSize = texture->getSize().x/3;

		if (tileSize*2 > size->x || tileSize*2 > size->y)
		{
			std::cout<< "Size of view too small for texture selected.\n";
		}
		else
		{
			destinationTexture->clear(sf::Color::Transparent);

			sf::Sprite tempSprite = sf::Sprite();

			tempSprite.setTexture(*texture);

			int verticalFillSpace = size->y;
			int verticalDrawingPoint = 0;

			while (verticalFillSpace > 0)
			{
				int referenceVerticalPoint = 0;

				//are we not filling the first line?
				if(verticalDrawingPoint)
				{
					//are we filling the bottom?
					if (verticalFillSpace <= tileSize)
					{
						referenceVerticalPoint = tileSize*2;
					}
					else
					{
						referenceVerticalPoint = tileSize;
					}
				}

				//we draw the left chunk
				tempSprite.setPosition(0.f,float(verticalDrawingPoint));
				tempSprite.setTextureRect(sf::IntRect(0,referenceVerticalPoint,tileSize,tileSize));
				destinationTexture->draw(tempSprite);

				//the right chunk
				tempSprite.setPosition(float(size->x-tileSize),float(verticalDrawingPoint));
				tempSprite.setTextureRect(sf::IntRect(tileSize*2,referenceVerticalPoint,tileSize,tileSize));
				destinationTexture->draw(tempSprite);

				int horizontalFillingSpace = size->x - (tileSize*2);
				int horizontalDrawingPoint = tileSize;

				tempSprite.setTextureRect(sf::IntRect(tileSize,referenceVerticalPoint,tileSize,tileSize));

				//now we fill the horizontal gap
				while (horizontalFillingSpace > 0)
				{
					//are we drawing the last one?
					if (horizontalFillingSpace<tileSize)
					{
						tempSprite.setTextureRect(sf::IntRect(tileSize,referenceVerticalPoint,horizontalFillingSpace,tileSize));
					}

					tempSprite.setPosition(float(horizontalDrawingPoint),float(verticalDrawingPoint));
					destinationTexture->draw(tempSprite);

					horizontalDrawingPoint +=tileSize;
					horizontalFillingSpace -= tileSize;
				}

				verticalFillSpace -= tileSize;

				if (verticalFillSpace < tileSize)
				{
					verticalDrawingPoint += verticalFillSpace;
				}
				else
				{
					verticalDrawingPoint += tileSize;
				}
			}
		}
	}
	else
	{
		if (alwaysUseClearBg)
		{
			destinationTexture->clear(sf::Color::Transparent);
		}
		else
		{
			destinationTexture->clear(sprite->getColor());
		}

	}

	if(text)
	{
		destinationTexture->draw(*text);
	}

	destinationTexture->display();

	if(finalTexture)
	{
		sprite->move(float(finalTexture->getSize().x)/2,float((finalTexture->getSize().y)/2));

		delete finalTexture;
	}

	finalTexture = new sf::Texture(destinationTexture->getTexture());

	delete destinationTexture;

	finalTexture->setSmooth(true);

	sprite->setTexture(*finalTexture);

	sprite->move(-float(finalTexture->getSize().x)/2,-float((finalTexture->getSize().y)/2));
}

void UIView::configInitialSettings(sf::Vector2i* newSize)
{
	drawAsPanel = false;
	focusedState = false;
	ignoreMouse = false;
	focusable = true;
	hoverable = false;
	beingHovered= false;
	alwaysUseClearBg = true;
	offset = new sf::Vector2i(0,0);
	setSize(newSize);
}




